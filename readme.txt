P pauses the game to allow interaction with the imgui windows. This stops the mouse pos being reset and displays the cursor

Checkpoint 1:
2nd Bullet feature is Raycasting. Aim toward the cube and press either X or LMB. In the Player ImGui window you will see the most recently hit object (if one was hit at all).

Checkpoint 2: Lighting works on more than 1 texture. See the gun model, which uses a texture and is light (gotta love that specular highlight)

Checkpoint 3: Scenes not push/pull themselves, it's not in Scene Manager.
Not sure what issue was with SoundPlayer, but now you can select what type of list to play in drop down menu (in Resource Manager ImGui panel). Code for these lists were created before this checkpoint,
but not the ImGui selection stuff

Checkpoint 4: Tweening used to animate Gun kickback (click LMB for visual).
To change the tween being used or how long the animation plays, adjust the TweenFunction, KickTime, and ResetTime
in the ImGui for the Handgun (in game objects)
Becareful editing the game time, it can break if you set it too long and click faster than the animation can reset.
Post-processing is done to change the scene to grayscale. To see this, press I.

Final: Goal of the game is to shoot all eyes before you die. Run into the wood box to pickup extra ammunition. Keep on the move to avoid the Eyeball's lasers.
WASD - Move
Spacebar - Jump
Left Click - Shoot
P - Pause
F9 - disable ImGui
R - Reset

OBS* Debug draw can be turned on on the phisics manager ImGui window. 

Known Issues: Every now and again the player gets some sort of "super" jump. This seems to be due to framerate issues with Bullet (try turning on all the debug drawing flags for extra fun, or extra frame drops, depends on your machine.).