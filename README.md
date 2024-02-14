# Geting Started 

1. Clone the Repository
2. Install QT [here]([url](https://www.qt.io/download-qt-installer?fbclid=IwAR3zChjUBHaVUdZoqmYDc_C3-_TKxPOkFtI2kKqzdsBhpS1R0h4HGqdej60)https://www.qt.io/download-qt-installer?fbclid=IwAR3zChjUBHaVUdZoqmYDc_C3-_TKxPOkFtI2kKqzdsBhpS1R0h4HGqdej60)
3. Open the project using the QT Creator
4. Build and run the program

# Features

The user can select between 4 modes: (1) add a single ball, (2) add multiple balls with a uniform distance between a given start and end point, (3) add multiple balls with uniform distance between the given start Θ and end Θ, and (4) add multiple balls with a uniform difference between the given start and end velocities.

To access the different input options, you can click on the tabs that reference each option. To access the other options outside the view you can click on the arrows beside them. You can also hover over the tabs and scroll the mouse wheel. 

The application also displays an FPS counter with the base frame-rate being 120 FPS. 

**(1) Single Ball Input**
| Input | Description |
|-------|-------------|
|Ball Location (X) | X-Position of the Ball |
|Ball Location (Y) | Y-Position of the Ball |
|Ball Velocity | Speed of the Ball |
|Ball Direction | Movement Direction of the Ball |

**(2) Multiple Balls Input (Different Positions):**
| Input | Description |
|-------|-------------|
|Initial Ball Location (X) | Starting X-Position in the Range |
|Final Ball Location (X) | Ending X-Position in the Range |
|Initial Ball Location (Y) | Starting Y-Position in the Range |
|Final Ball Location (Y) | Ending Y-Position in the Range |
|Ball Velocity | Speed of the Balls |
|Ball Direction | Movement Direction of the Balls |
|Number of Balls | Number of Balls to be Added|

**(3) Multiple Balls Input (Different Movement Directions):**
| Input | Description |
|-------|-------------|
|Initial Direction | Starting Movement Direction in the Range |
|Final Direction | Ending Movement Direction in the Range |
|Ball Location (X) | X-Position of the Balls |
|Ball Location (Y) | Y-Position of the Balls |
|Ball Velocity | Speed of the Balls |
|Number of Balls | Number of Balls to be Added|

**(4) Multiple Balls Input (Different Velocities):**
| Input | Description |
|-------|-------------|
|Initial Velocity | Starting Velocity in the Range |
|Final Velocity | Ending Velocity in the Range |
|Ball Location (X) | X-Position of the Balls |
|Ball Location (Y) | Y-Position of the Balls |
|Ball Direction | Movement Direction of the Balls |
|Number of Balls | Number of Balls to be Added|

# Important Information

- The application may occasionally crash when adding balls. You can rerun the application again with the same input to retest the add-on configuration.

- Please only input X-position from 0 to 1280, and Y-positions from 0 to 720. 

- Please only input velocities from 0 to 8. 
    - Inputting negative velocities will cause the wall collision to fail. 
    - Inputting velocities over 8 may also cause the ball to pass through the wall instead of bouncing on it.

- Movement Directions starts on the positive X and goes counter-clockwise. 
    - 0 will cause the ball to move rightward
    - 90 will cause the ball to move upwards
    - 180 causes the ball to move leftwards
    - 270 causes the ball to go downwards

- If the frame rate drops significantly, the ball movement may be affected.

- If you see the balls leave a trail, this is only a UI glitch, you can remove it by reloading the application 
    - (ie. minimize and reopen the app, or clicking on a different app and clicking back to the program to reload the scene)


# Authors

Caoile, Sean Iverson

Tan, Gavin Matthew 
