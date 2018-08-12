"""2D Physics environment, based on Box2D.

Provides per-frame simulation, event callbacks, and input handling.
"""
from rl.box2d.app import framework

from Box2D import b2


class Environment(framework.Framework):

  name = "2D Environment"  # Name of the class to display
  description = "2D physics simulation"

  def __init__(self):
    """
    Initialize all of your objects here.
    Be sure to call the Framework's initializer first.
    """
    super().__init__(gravity=(0, 0))

    # wall_body = self.world.CreateBody(position=(0, -10))
    # wall_box = b2.polygonShape(box=(50, 10))
    # wall_body.CreateFixture(shape=wall_box)

    # wall_body = self.world.CreateStaticBody(
    #     position=(0, -10),
    #     shapes=[b2.polygonShape(box=(50, 10)),
    #             b2.polygonShape(box=(10, 50))],
    # )

    # The boundaries.
    play_area = self.world.CreateBody(position=(0, 20))
    play_area.CreateEdgeChain(
      [(-20, -20), (-20, 20), (20, 20), (20, -20), (-20, -20)]
    )

    box1 = self.world.CreateDynamicBody(position=(0, 4))
    box1.CreatePolygonFixture(box=(1, 1), density=1, friction=0.3)

    box2 = self.world.CreateDynamicBody(
      position=(3, 4),
      angle=0,
      linearDamping=1,
      angularDamping=1,
      shapes=b2.polygonShape(box=(1, 1)),
      shapeFixture=b2.fixtureDef(density=1, friction=0.3)
    )

  def Keyboard(self, key):
    """
    The key is from Keys.K_*
    (e.g., if key == Keys.K_z: ... )
    """
    pass

  def Step(self, settings):
    """Called upon every step.
    You should always call
     -> super().Step(settings)
    at the beginning or end of your function.

    If placed at the beginning, it will cause the actual physics step to happen first.
    If placed at the end, it will cause the physics step to happen after your code.
    """

    super().Step(settings)

    # do stuff

    # Placed after the physics step, it will draw on top of physics objects
    self.Print("*** Base your own testbeds on me! ***")

  def ShapeDestroyed(self, shape):
    """
    Callback indicating 'shape' has been destroyed.
    """
    pass

  def JointDestroyed(self, joint):
    """
    The joint passed in was removed.
    """
    pass


if __name__ == "__main__":
  framework.main(Environment)