#include "GameCore.h"
#include "CommandParser.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <conio.h>


namespace TextGame
{
	RoomData CreateRoom(const std::string& inName, const std::string& inDescription)
	{
		RoomData room = {};
		room.Name = inName;
		room.Description = inDescription;

		return room;
	}

	void InitializeGame(PlayerState& playerState, WorldState& worldState)
	{
		printf("Welcome to...\n");
		printf("A GAME by SOMEONE\n\n");
		printf("TELL THE PLAYER THE GOAL OF THE GAME\n\n");

		playerState.WantsDescription = true;
		playerState.CurrentRoomIndex = 0;
		playerState.CurrentPosition.X = 5;
		playerState.CurrentPosition.Y = 3;

		
		//playerState.Inventory.push_back({ ItemType_KEY, Position() });
		//playerState.Inventory.push_back({ ItemType_SWORD, Position() });
		//playerState.Inventory.push_back({ ItemType_KEY, Position() });

		worldState.Rooms.clear();

		// 0
		{
			RoomData room = CreateRoom("Well", "You were standing outside of a well to get water when you accidentally fell in. It’s cold, dark, and wet at the bottom, but at least it's roomy.  You see two possible openings you can crawl through. There is also something sticking out of the ground.");

			room.RoomMapWidth = 8; //each row is 8 characters
			room.RoomPosition = { 0,0 };
			room.RoomMap = 
				"###..###"
				"#......#"
				"#......#"
				"........"
				"#......#"
				"#......#"
				"########";

			
			room.Inventory.push_back({ ItemType_SWORD, {2,2} });

			room.LockedDoors.push_back({ {7,3} });

			worldState.Rooms.push_back(room);
		}
		// 1
		{
			RoomData room = CreateRoom("Armory", "This armory is half buried in dirt. It seems like the ceiling had collapsed a long time ago. There is only a lone sword left out of the countless, empty weapon stands.");

			room.RoomMapWidth = 8; //each row is 8 characters
			room.RoomPosition = { 1,0 };
			room.RoomMap =
				"########"
				"#......#"
				"#......#"
				".......#"
				"#......#"
				"#......#"
				"###..###";

			room.Inventory.push_back({ ItemType_SWORD, {3,2} });

			worldState.Rooms.push_back(room);
		}
		// 2
		{
			RoomData room = CreateRoom("Stone Hallway", "You find yourself in a stone hallway. The crates and barrels littering the floor are covered in a layer of grime and dust.");

			room.RoomMapWidth = 8; //each row is 8 characters
			room.RoomPosition = { 0, -1 };
			room.RoomMap =
				"###..###"
				"#....#.#"
				"#......#"
				"#..##..#"
				"#.#....#"
				"#......#"
				"###..###";

			worldState.Rooms.push_back(room);
		}
		// 3
		{
			RoomData room = CreateRoom("Lavish Hallway", "There are ornate paintings covering the walls as well as candelabras whose wax candles melted away long ago.");

			room.RoomMapWidth = 8; //each row is 8 characters
			room.RoomPosition = { 1, 1 };
			room.RoomMap =
				"###..###"
				"#......#"
				"#......#"
				"#......."
				"#......#"
				"#......#"
				"########";

			worldState.Rooms.push_back(room);
		}
		// 4
		{
			RoomData room = CreateRoom("Throne Room", "This is the most intact room you’ve found in this buried castle. There are gold furnishings everywhere, even in the dark you are blinded by the glittering of gold. The throne at the end of the room is still as regal as it must have been centuries before.");

			room.RoomMapWidth = 8; //each row is 8 characters
			room.RoomPosition = { 2, 1 };
			room.RoomMap =
				"########"
				"#..##..#"
				"#......#"
				".......#"
				"#......#"
				"#......#"
				"########";

			room.Inventory.push_back({ ItemType_CROWN, {4,2} });

			worldState.Rooms.push_back(room);
		}
		// 5
		{
			RoomData room = CreateRoom("Kitchen", "You find yourself in a desolate kitchen forgotten by time. It seems a long time ago it was a part of a larger structure that got buried and forgotten by the outside world.");

			room.RoomMapWidth = 8; //each row is 8 characters
			room.RoomPosition = { -1, 0 };
			room.RoomMap =
				"########"
				"#......#"
				"#......#"
				"#......."
				"#......#"
				"#......#"
				"########";

			room.Inventory.push_back({ ItemType_KEY, {2,3} });

			worldState.Rooms.push_back(room);
		}
	}

	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		playerState.WantsToExit = false;
		playerState.WantsDescription = false;
		playerState.WantsInventoryListed = false;
		playerState.DesiredPosition = playerState.CurrentPosition;
		playerState.WantsToGet = false;
		playerState.WantsToWin = false;


		printf("What do you do?\n");
		printf("> ");

		TextAdventureCommand command = ParseAdventureCommand();

		/*TextAdventureCommand command = {};
		command.Verb = "";
		while (command.Verb == "")
		{
			char key = _getch();

			if (key == 'A' || key == 'a') command.Verb = "a";
			else if (key == 'W' || key == 'w') command.Verb = "w";
			else if (key == 'S' || key == 's') command.Verb = "s";
			else if (key == 'D' || key == 'd') command.Verb = "d";
			else if (key == 'C' || key == 'c') command.Verb = "commandMode";
		}

		if (command.Verb == "commandMode") {
			printf("COMMAND MODE:");
			command = ParseAdventureCommand();
		}*/

		if (command.Verb == "quit")
		{
			playerState.WantsToExit = true;
		}
		else if (command.Verb == "north" || command.Verb == "n")
		{
			playerState.DesiredPosition.Y = playerState.CurrentPosition.Y - 1;
		}
		else if (command.Verb == "south" || command.Verb == "s")
		{
			playerState.DesiredPosition.Y = playerState.CurrentPosition.Y + 1;
		}
		else if (command.Verb == "west" || command.Verb == "w")
		{
			playerState.DesiredPosition.X = playerState.CurrentPosition.X - 1;
		}
		else if (command.Verb == "east" || command.Verb == "e")
		{
			playerState.DesiredPosition.X = playerState.CurrentPosition.X + 1;
		}
		else if (command.Verb == "look")
		{
			playerState.WantsDescription = true;
		}
		else if (command.Verb == "inventory" || command.Verb == "inv")
		{
			playerState.WantsInventoryListed = true;
		}
		else if (command.Verb == "get")
		{
			playerState.WantsToGet = true;
		}
		else if (command.Verb == "win")
		{
			playerState.WantsToWin = true;
		}
		else if (command.Verb == "help")
		{
			printf("Command List: look, quit, inventory, get, north, south, west, east\n");
			printf("Key:\n");
			printf("  @ - Player\n");
			printf("  A - Altar\n");
			printf("  i - Item\n");
			printf("  . - Floor\n");
			printf("  # - Wall\n");
			printf("  H - Door (Locked)\n");
		}
		else
		{
			printf("I don't understand\n");
		}
		printf("\n");

	}

	void RenderGame(const PlayerState& playerState, const WorldState& worldState)
	{
		if (playerState.WantsDescription)
		{
			const RoomData& currRoom = worldState.Rooms[playerState.CurrentRoomIndex];
			printf("================================================\n");
			printf("LOCATION: %s\n", currRoom.Name.c_str());
			printf("%s\n\n", currRoom.Description.c_str());
			
			std::string renderedMapString = "";
			int currentSpace = 0;
			while (currentSpace < currRoom.RoomMap.size())
			{
				char characterToDisplay = currRoom.RoomMap[currentSpace];

				for (unsigned int i = 0; i < currRoom.Inventory.size(); ++i)
				{
					const InventoryItem& currItem = currRoom.Inventory[i];
					if (PositionToIndex(currItem.ItemPosition, currRoom.RoomMapWidth) == currentSpace)
					{
						characterToDisplay = GetItemIcon(currItem.Type);
					}
				}

				for (unsigned int i = 0; i < currRoom.LockedDoors.size(); ++i)
				{
					const LockedDoorData& currDoor = currRoom.LockedDoors[i];
					if (PositionToIndex(currDoor.DoorPosition, currRoom.RoomMapWidth) == currentSpace)
					{
						characterToDisplay = 'H'; //was D
					}
				}

				if (PositionToIndex(playerState.CurrentPosition, currRoom.RoomMapWidth) == currentSpace) //if player is here, replace charactertoDisplay with @
				{
					characterToDisplay = '@';
				}

				

				renderedMapString += characterToDisplay;

				if (currentSpace % currRoom.RoomMapWidth == (currRoom.RoomMapWidth - 1) )
				{
					renderedMapString += '\n';
				}

				currentSpace++;
			}

			printf("%s\n", renderedMapString.c_str());

			printf("\n");
		}
		else if (playerState.WantsInventoryListed)
		{
			printf("================================================\n");
			printf("INVENTORY:\n");

			if (playerState.Inventory.size() == 0)
			{
				printf("You have nothing...\n");
			}

			for (unsigned int i = 0; i < playerState.Inventory.size(); ++i)
			{
				printf("%s\n", GetItemName(playerState.Inventory[i].Type).c_str());
			}

			printf("\n");
		}
	}

	void UpdateGame(PlayerState& playerState, WorldState& worldState)
	{
		RoomData& currRoom = worldState.Rooms[playerState.CurrentRoomIndex];
		
		if (playerState.DesiredPosition != playerState.CurrentPosition)
		{

			TryToUnlockDoor(playerState.DesiredPosition, currRoom, playerState);

			if (IsSpaceOutsideMap(playerState.DesiredPosition, currRoom))
			{
				Position desiredRoomPosition = currRoom.RoomPosition;
				int playerPositionType = 0;

				if (playerState.DesiredPosition.X < 0)
				{
					desiredRoomPosition.X--;
					playerPositionType = 1;
				}
				else if (playerState.DesiredPosition.X >= currRoom.RoomMapWidth)
				{
					desiredRoomPosition.X++;
					playerPositionType = 2;
				}
				else if (playerState.DesiredPosition.Y < 0)
				{
					desiredRoomPosition.Y--;
					playerPositionType = 3;
				}
				else if (playerState.DesiredPosition.Y >= ((int)currRoom.RoomMap.size() / currRoom.RoomMapWidth))
				{
					desiredRoomPosition.Y++;
					playerPositionType = 4;
			    }

				bool foundNewRoom = false;
				for (unsigned int i = 0; i < worldState.Rooms.size(); ++i)
				{
					if (worldState.Rooms[i].RoomPosition == desiredRoomPosition)
					{
						playerState.CurrentRoomIndex = i;
						playerState.WantsDescription = true;

						switch (playerPositionType)
						{
						case 1:
							playerState.CurrentPosition.X = worldState.Rooms[playerState.CurrentRoomIndex].RoomMapWidth - 1;
							break;
						case 2:
							playerState.CurrentPosition.X = 0;
							break;
						case 3:
							playerState.CurrentPosition.Y = (worldState.Rooms[playerState.CurrentRoomIndex].RoomMap.size() / worldState.Rooms[playerState.CurrentRoomIndex].RoomMapWidth) - 1;
							break;
						case 4:
							playerState.CurrentPosition.Y = 0;
							break;
						}

						foundNewRoom = true;
					}
				}

				if (!foundNewRoom)
				{
					printf("Nothing but void out there!\n");
				}
				
			}
			else if (IsSpaceOpenForMovement(playerState.DesiredPosition, currRoom))
			{
				playerState.CurrentPosition = playerState.DesiredPosition;
				playerState.WantsDescription = true;
			}
			else
			{
				printf("That path is blocked!\n");
			}
		}
		else if (playerState.WantsToGet)
		{
			bool foundItem = false;
			for (unsigned int i = 0; i < currRoom.Inventory.size(); ++i)
			{
				const InventoryItem& currItem = currRoom.Inventory[i];
				if (currItem.ItemPosition == playerState.CurrentPosition)
				{
					printf("I got an '%s'\n", GetItemName(currItem.Type).c_str());

					playerState.Inventory.push_back(currItem);

					currRoom.Inventory.erase(currRoom.Inventory.begin() + i);

					foundItem = true;
					break;
				}
			}

			if (!foundItem)
			{
				printf("There is nothing there to get \n");
			}
		}
		else if (playerState.WantsToWin)
		{
			

			int numberOfCrowns = 0;
			int numberOfSwords = 0;

			for (unsigned int i = 0; i < playerState.Inventory.size(); ++i)
			{
				const InventoryItem& currItem = playerState.Inventory[i];
				if (currItem.Type == ItemType_CROWN)
				{
					numberOfCrowns++;
				}
				else if (currItem.Type == ItemType_SWORD)
				{
					numberOfSwords++;
				}
			}

			if (numberOfCrowns >= 1 && numberOfSwords >= 2)
			{
				printf("An old man appears and says: \n Yes! You have the items needed to be the ruler of our kingdom! \n\n");
				playerState.WantsToExit = true;
			}
			else
			{
				
				printf("An old man appears and says: \n No! You must have both SWORDS and the CROWN to win! \n");
			}
		}
	}

	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		worldState.Rooms.clear();
	}

	int PositionToIndex(const Position& position, int roomWidth)
	{
		return position.Y * roomWidth + position.X;
	}

	bool IsSpaceOpenForMovement(const Position& position, const RoomData& currRoom)
	{
		for (unsigned int i = 0; i < currRoom.LockedDoors.size(); ++i)
		{
			const LockedDoorData& currDoor = currRoom.LockedDoors[i];
			if (currDoor.DoorPosition == position)
			{
				return false;
			}
		}
		
		int spaceIndex = PositionToIndex(position, currRoom.RoomMapWidth);
		return currRoom.RoomMap[spaceIndex] == '.';
	}
	bool IsSpaceOutsideMap(const Position& position, const RoomData& currRoom)
	{
		return position.X < 0 ||
			position.X >= currRoom.RoomMapWidth ||
			position.Y < 0 ||
			position.Y >= ((int)currRoom.RoomMap.size() / currRoom.RoomMapWidth);
	}

	void TryToUnlockDoor(const Position& position, RoomData& currRoom, PlayerState& playerState)
	{
		for (unsigned int i = 0; i < currRoom.LockedDoors.size(); ++i)
		{
			const LockedDoorData& currDoor = currRoom.LockedDoors[i];
			if (currDoor.DoorPosition == position)
			{
				//we found a door, now lets find the players key

				for (unsigned int j = 0; j < playerState.Inventory.size(); ++j)
				{
					const InventoryItem& currItem = playerState.Inventory[j];
					if (currItem.Type == ItemType_KEY)
					{
						//found a key
						currRoom.LockedDoors.erase(currRoom.LockedDoors.begin() + i);
						playerState.Inventory.erase(playerState.Inventory.begin() + j);

						return;
					}
				}
			}
		}

	}

	std::string GetItemName(ItemType itemType)
	{
		switch (itemType)
		{
		case ItemType_KEY:
			return "Shiny Key";
			break;
		case ItemType_SWORD:
			return "Rusty Sword";
			break;
		case ItemType_CROWN:
			return "Glittering Crown";
			break;
		}

		return "Unknown Item";
	}

	char GetItemIcon(ItemType itemType)
	{
		switch (itemType)
		{
		case TextGame::ItemType_KEY:
			return 'k';
			break;
		case TextGame::ItemType_SWORD:
			return 's';
			break;
		case TextGame::ItemType_CROWN:
			return 'c';
			break;
		}
		return 'i';
	}
}
