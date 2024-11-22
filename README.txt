Use the given game engine to create the following. Make sure to add appropriate classes
if required. Include a text (READMe.txt) file outlining your task and approach.
Submit your complete work as in compressed (zip) file to the link in blackboard. If your
program not running in a remote machine you may not get complete marks. Therefore,
make sure your program runs without errors. Your creativity will be awarded extra 5
points.
1) Load 3D Model as player
2) Have two animations for a player (run and jump)
3) Move the parallax opposite direction of the player running
4) Have random 3D objects move towards the player
5) Make player jump over objects with jump animation (up key pressed)
6) Make objects disappear if player collide
7) Include 3 levels each completion after avoid 6 objects


My approach was to get enemies to spawn and then work on the rest from there. I had to divorce the modelloader from a lot of stuff like controls because the model loader was also being used to load enemy models. I created a new enemyManager class and used that to handle
most enemy logic and behavior. I had my main character stationary in the center, and everything else moves to the left. This makes collisions easier to handle. Then I added a jump mechanic and tied that into the collisions.

Once I had that I just had to add score tracking and different parallax views for the different levels. I tied that into score, so once score goes past 60 it advances the level. 