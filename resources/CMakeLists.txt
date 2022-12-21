#file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)

# Enemies
configure_file ("CharacterImages/Demon.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("CharacterImages/Dragon.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("CharacterImages/DarkCleric.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("CharacterImages/Wolf.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Players
configure_file ("CharacterImages/wizard.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("CharacterImages/archer.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("CharacterImages/cleric.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("CharacterImages/knight.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Backgrounds and utility
configure_file ("Backgrounds/help.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Backgrounds/settings.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Backgrounds/levelSelectBG.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Backgrounds/menuBG.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Backgrounds/skillInfoBG.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("plain.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("snowlands.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("firelands.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("select.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Skills
configure_file ("skills/heal.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/shield.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/swing.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/clericShield.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/barrage.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/apolloarrow.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/aimedshot.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/debilitate.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/intimidate.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/drainlife.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/lightningIcon.png" ${CMAKE_BINARY_DIR} COPYONLY)

configure_file ("skills/clericBasic.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/wizardBasic.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/knightBasic.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/archerBasic.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Fonts
configure_file ("POORICH.TTF" ${CMAKE_BINARY_DIR} COPYONLY)

# Projectiles
configure_file ("proj/healProj.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("proj/FireBlast.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("proj/arrow.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("proj/fireBreath.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("proj/water_strike.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("proj/tesla_ball.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("proj/lightning.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("proj/energy.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Levels files
configure_file ("Levels.txt" ${CMAKE_BINARY_DIR} COPYONLY)

# Menu and LV Select
configure_file ("MenuImages/currentLevelIcon.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("MenuImages/levelSelection.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("MenuImages/levelCompleted.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("MenuImages/startButton.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("MenuImages/startButtonHL.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Buttons
configure_file ("Buttons/skillHover.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/pauseButton.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/pauseButtonHL.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/continueButton.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/continueButtonHL.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/restartButton.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/restartButtonHL.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/exitButton.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/exitButtonHL.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/volInc.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/volIncHL.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/volDec.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/volDecHL.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/volMute.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Buttons/volMuteHL.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Game states
configure_file ("GameStates/Defeat.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("GameStates/Pause.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("GameStates/Victory.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Sounds
configure_file ("Audio/battle.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/buttonClick.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/clickPlayer.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/hoverSound.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/movePlayer.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/levelMusic1.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/levelMusic2.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/menuMusic.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/sword1.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/sword2.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/arrow.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/arrow_rain.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/defence_buff.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Audio/heal.wav" ${CMAKE_BINARY_DIR} COPYONLY)
