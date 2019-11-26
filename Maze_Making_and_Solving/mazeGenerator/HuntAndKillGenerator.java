package mazeGenerator;

import maze.Maze;
import java.util.Random;
import maze.Cell;

public class HuntAndKillGenerator implements MazeGenerator {
	public int dirs[] = {Maze.NORTH, Maze.SOUTH, Maze.EAST, Maze.WEST};
	public Random rand = new Random(System.currentTimeMillis());

	@Override
	public void generateMaze(Maze maze) {

		//initial run
		//start by selecting a random cell in the maze
		int c = randomCoord(maze.sizeC);
		int r = randomCoord(maze.sizeR);
		boolean deadEnd = false;

		//while the current cell has an unvisited cell to move to, keep moving
		while (!deadEnd){
			//check if there is a tunnel at the cell
			if (maze.map[r][c].tunnelTo != null){
				Cell jump = maze.map[r][c].tunnelTo;
				// jump to the oppposite end of the tunnel - set the coords to the end's coords
				r = jump.r;
				c = jump.c;
			}
			//pick a direction to move in
			int direction = randomDir(maze.map[r][c]);

			//no valid cells to visit from the current one; kill the loop
			if (direction == -1){
				deadEnd = true;
			}

			else{
				//remove the current wall
				maze.map[r][c].wall[direction].present = false;

				// move to the next cell
				r += maze.deltaR[direction];
				c += maze.deltaC[direction];

				//remove the neighbour wall
				maze.map[r][c].wall[maze.oppoDir[direction]].present = false;
			}
		}	

		//fill out the rest of the maze
		Cell unvisited = scanGrid(maze);
		while(unvisited != null){
			//remove the wall between the next cell and an adjacent visited cell

			deadEnd = false;
			r = unvisited.r;
			c = unvisited.c;

			while (!deadEnd){

				if (maze.map[r][c].tunnelTo != null){
					Cell jump = maze.map[r][c].tunnelTo;
					// jump to the oppposite end of the tunnel - set the coords to the end's coords
					r = jump.r;
					c = jump.c;
				}	

				//pick a direction to move in
				int direction = randomDir(maze.map[r][c]);

				//no valid cells to visit from the current one; kill the loop
				if (direction == -1){
					deadEnd = true;
				}
 
				else{
					//remove the current wall
					maze.map[r][c].wall[direction].present = false;

					// move to the next cell
					r += maze.deltaR[direction];
					c += maze.deltaC[direction];

					//remove the neighbour wall
					maze.map[r][c].wall[maze.oppoDir[direction]].present = false;
					//System.out.println("currently at cell: (" + c + ", " + r + ")"); 
				}
			}

			unvisited = scanGrid(maze);
		}
	}
		// exits when there are no more cells to visit
		// maze generation is complete

	 // end of generateMaze()

	// see if a neighbour has already been visited (missing walls)
	public boolean checkNeighbour(Cell neighbour){
		boolean unvis = true;
		int i = 0;

		if (neighbour != null){
			while (i < dirs.length && unvis == true){
				//if there isn't a wall set false
				if (neighbour.wall[dirs[i]].present == false){
					unvis = false;
				}
				i++;
			}
		}

		//out of bounds; ignore
		else{
			unvis = false;
		}
		return unvis;
	}

	//determine wether a cell has been visited or not
	public boolean cellVisit(Cell curr){
		boolean val = true;
		for (int i = 0; i < dirs.length; i++){
			if (curr.wall[dirs[i]].present == false && curr.neigh[dirs[i]] != null){
				val = false;
			}
		}
		return val;
	}
	
	//generate a random x or y-coord
	public int randomCoord(int axisLim){
		return rand.nextInt(axisLim);
	}

	// select and validate a random direction
	public int randomDir(Cell curr){
		// randomise the order of directions
		int[] rDirs = dirs;
		int dir = -1;

		//shuffle directions
		for (int i = rDirs.length - 1; i > 0; i --){
			int idx = rand.nextInt(i + 1);
			int d = rDirs[idx];

			rDirs[idx] = rDirs[i];
			rDirs[i] = d; 
 		}
 		// find a direction that leads to an unvisited cell
 		int j = 0;
 		while (dir == -1 && j < rDirs.length){
 			if (checkNeighbour(curr.neigh[rDirs[j]])){
 				dir = rDirs[j];
 			}
 			j++;
 		}

 		return dir;
	}

	// move through the maze cells to find the next unvisited cell
	public Cell scanGrid(Maze maze){
		int row = 0;
		int col = 0;
		Cell unvis = null;
		//move up through the rows to the top		
		while(row < maze.sizeR && unvis == null){
			col = 0;
			while( col < maze.sizeC && unvis == null){
				unvis = huntedCell(maze, row, col);
				col++;
			}
			row++;
		}

		return unvis;
	}

	public Cell huntedCell(Maze maze, int row, int col){
		Cell target = null;
		if (cellVisit(maze.map[row][col])){
			int i = 0;
			while (i < dirs.length && target == null){
				// if the cell neighbour exists and has been visited
				if(maze.map[row][col].neigh[dirs[i]] != null && checkNeighbour(maze.map[row][col].neigh[dirs[i]]) == false){
					//get the new cell
					target = maze.map[row][col];

					//break down the wall between the new and the visited adjacent
					maze.map[row][col].wall[dirs[i]].present = false;
					int dr = maze.deltaR[dirs[i]];
					int dc = maze.deltaC[dirs[i]];
					maze.map[row + dr][col + dc].wall[maze.oppoDir[dirs[i]]].present = false; //wew
				}
				i++;
			}
		}
		return target;
	}
} // end of class HuntAndKillGenerator
