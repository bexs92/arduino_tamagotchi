# arduino_tamagotchi
Personal tamagotchi project

08/11/25 DEV_002 - making adjustments to sprite_library to remove all the extra references to statemachine.

10/11/25 created a encyclopedia library to handle all data that always stay the same. Wanting to merge DEV_002 into dev

10/11/25 merged DEV_002 into dev, about to delete dev

11/11/25 Added the data struct into the tamagotchi library and added the variables to the tamagotchi class. I've also added a save and load from card. This is working and the character is loading from the card. Need to add a save menu. I tried using a save every x seconds but it didn't work. I'm assuming it can't boot and shut down the card fast enough for that sort of thing.

01/03/26 - Merged branch DEV_016 created anim sequence system and converted a couple animations to this method. The rest of the animations need to be changed and I may need to add the ability to pick the sprite sheet per sequence instead of once per comp. This will be opened again in isssue DEV_018, closing DEV_016 for now

01/03/26 - Merged DEV_010, added a basic scrolling function for the first stat page.
