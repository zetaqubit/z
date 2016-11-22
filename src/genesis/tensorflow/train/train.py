"""Trains the hand-tracking network.

"""
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import os
import tensorflow as tf

flags = tf.app.flags
FLAGS = flags.FLAGS
flags.DEFINE_string('data_dir',
                    '/home/z/code/blaze_root/data/genesis/current/tf',
                    'Directory for storing data')
flags.DEFINE_string('summaries_dir',
                    '/tmp/genesis_logs',
                    'Summaries directory')

# Training configs
kBatchSize = 32
kShuffleCapacity = 500
kLearningRate = 0.001
kMaxSteps = 1000

# Constants. Keep in sync with //src/genesis/io/datatypes.h
kNNImageWidth = 128
kNNImageHeight = 128
kHeatmapWidth = 16
kHeatmapHeight = 16

def read_and_decode_batch():
  # Read single example
  filename_queue = tf.train.string_input_producer(
      [os.path.join(FLAGS.data_dir, 'frames.tfrecords')])
  reader = tf.TFRecordReader()
  key, serialized_example = reader.read(filename_queue)
  features = tf.parse_single_example(
      serialized_example,
      features={
        'left_image': tf.FixedLenFeature([kNNImageWidth, kNNImageHeight],
            dtype=tf.float32),
        'left_palm': tf.FixedLenFeature([kHeatmapWidth, kHeatmapHeight],
            dtype=tf.float32)
      })
  image = features['left_image']
  label = features['left_palm']

  # Shuffle and batch
  images, labels = tf.train.shuffle_batch(
      [image, label], batch_size=kBatchSize,
      num_threads=2,
      capacity=kShuffleCapacity + 3 * kBatchSize,
      min_after_dequeue=kShuffleCapacity)

  images = tf.reshape(images, [-1, kNNImageWidth, kNNImageHeight, 1])
  labels = tf.reshape(labels, [-1, kHeatmapWidth, kHeatmapHeight, 1])
  return images, labels


def inference(images):
  def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

  def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

  def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

  def max_pool(x, width, stride):
    return tf.nn.max_pool(
        x, ksize=[1, width, width, 1], strides=[1, stride, stride, 1],
        padding='SAME')

  W_conv1 = weight_variable([5, 5, 1, 32])
  b_conv1 = bias_variable([32])
  h_conv1 = tf.nn.relu(conv2d(images, W_conv1) + b_conv1)
  h_pool1 = max_pool(h_conv1, 2, 2)

  W_conv2 = weight_variable([5, 5, 32, 64])
  b_conv2 = bias_variable([64])
  h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
  h_pool2 = max_pool(h_conv2, 2, 2)

  W_conv3 = weight_variable([5, 5, 64, 64])
  b_conv3 = bias_variable([64])
  h_conv3 = tf.nn.relu(conv2d(h_pool2, W_conv3) + b_conv3)
  h_pool3 = max_pool(h_conv3, 2, 2)

  W_conv4 = weight_variable([5, 5, 64, 1])
  b_conv4 = bias_variable([1])
  h_conv4 = conv2d(h_pool3, W_conv4) + b_conv4

  return h_conv4


def minimize_loss(target, output):
  loss = tf.nn.l2_loss(target - output)
  train_step = tf.train.AdamOptimizer(kLearningRate).minimize(loss)
  return loss, train_step


def main(_):
  with tf.Graph().as_default():
    images, labels = read_and_decode_batch()
    output = inference(images)
    loss, train_step = minimize_loss(labels, output)

    # Initialize
    sess = tf.Session()
    init_op = tf.group(tf.initialize_all_variables(),
                       tf.initialize_local_variables())
    sess.run(init_op)
    coord = tf.train.Coordinator()
    threads = tf.train.start_queue_runners(sess=sess, coord=coord)

    print('Starting training.')

    try:
      step = 0
      while not coord.should_stop() and step < kMaxSteps:
        _, loss_val = sess.run([train_step, loss])
        step += 1
        if step % 1 == 0:
          print('Step %d: loss = %.2f' % (step, loss_val))
    finally:
      coord.request_stop()

    # Wait for threads to finish
    coord.join(threads)
    sess.close()


if __name__ == '__main__':
  tf.app.run()
