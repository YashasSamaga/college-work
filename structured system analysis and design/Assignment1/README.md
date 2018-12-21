### How to run?
```python3 main.py```

### Notes

*All mandatory requirements have been met (except for boss enemy)*

Additional features:
- basic animation for mario's left-right movement
- mario grows (baby mario, teen mario, adult mario)
  - teen mario has the ability to crush enemies
- enemy follows player (and jumps)
- realistic physics:
  - you cannot move left or right while in air (you need to be on a surface to move horizontally)
    - underwater world is an exception; the water's drag lets you move around anywhere
  - different materials have different friction and elasticity property
  - gravity + terminal velocity
- world and levels system
  - world is composed of multiple levels
  - levels switch automatically
- levels are stored in /data/worlds/<worldid>/<levelid> folder
  - each level has a scene file and a meta file
  - scene file encodes the background information
  - meta file stores configuration for the level (such as drag)
- sounds (including level music)
- full complete UI
  - menu, gameover, level begining, etc. screens
- supports score, lives, time
- supports wrap levels (example not implemented though)

*NOT ALL OF THE AUDIO FILES HAVE NOT BEEN UPLOADED AS ANNOUNCED*
