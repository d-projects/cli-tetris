### Quadris
Quadris is a similar game to Tetris. However, it is a static game and does not support animated movement. Commands should be entered on the CLI and output can be seen on the CLI and/or the GUI.

## Starting the Game
- Run `make` to compile the code.
- Start the game without the optional flags with `./quadris`
- Optional starting flags can be set as follows: `./quadris -seed 42`

## Starting Flags
All of the below commands are optional.
- `-text`: Makes the game text only
- `-seed <seed value>`: Randomizes the block generation based on the seed (default seed is 0)
- `-scriptfile <file name>`: Determines block order from the given file (default file is "sequence.txt")
- `-startlevel <level number>`: Sets the level the game will start at (default level is 0)

## Gameplay Commands
- `left`: Moves the block to the left if possible. A multiplier preceeding the command will move it to the maximum possible distance left that is less than or equal to the multiplier (e.g `5left`).
- `right`/`up`/`down`: Same as `left`, but in the right/up/down direction.
- `clockwise`/`counterclockwise`: Rotates the block 90 degrees in the given direction.
- `drop`: Drops a block if possible. A multiplier, m, will drop m blocks (unless the end of the game is reached).
- `levelup/leveldown`: Levels up/down if possible (e.g. if not at level 4 or 0). A multiplier will default to level 0 or 4 if its value is too high.
- `norandom`: Only accepts the command during level 3/4. An invalid file is not accepted and will re-prompt for a new command. Infinitely loops through the blocks in the given file, instead of generating block randomly.
- `random`: Only accepts the command during level 3/4. Resets random generation of blocks.
- `sequence <file name>`: Executes the commands in the file from start to end. After completion, prompts for more commands. Also handles recursive sequence commands (i.e. sequence commands in the given command file).
`I`/`J`/`L`/`S`/`Z`/`O`/`T`: Replaces the current block with the entered block. Spwans at the top left (initial block) position. The level of the block is set to the level of the game at that point in time.
- `restart`: Restarts the game. Will set the level to level 0 but keep the seed and scriptfile (if provided at the beginning) the same

Any shortened version of a command that is able to distinguish it from all other commands can be used as well (e.g. `ri` instead of `right`).

## Contributors
- Dulhan Waduge
- Matthew Geng
- Alison Zhang