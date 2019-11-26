package mazeSolver;

import maze.Maze;
import maze.Cell;
import java.util.*;

/**
 * Implements the recursive backtracking maze solving algorithm.
 */
public class RecursiveBacktrackerSolver implements MazeSolver {
	public Random rand = new Random(System.currentTimeMillis());
	public boolean solution;
	public int counter = 0;
	public int[]  dirs = {Maze.NORTH, Maze.SOUTH, Maze.EAST, Maze.WEST};
	public int[] oDirs = Maze.oppoDir;

	@Override
	public void solveMaze(Maze maze) {
		// TODO Auto-generated method stub

		//start at the entrance
		solution = searchMaze(maze, -1, maze.entrance, maze.exit);

	} // end of solveMaze()

	public boolean searchMaze(Maze maze, int dir, Cell curr, Cell target){
		boolean found = false;
		maze.drawFtPrt(curr);
		counter++;
		if (curr.r == target.r && curr.c == target.c){
			found = true;
		}

		//if there is tunnel, move through it
		else if( curr.tunnelTo != null){
			maze.drawFtPrt(curr.tunnelTo);

			ArrayList<Integer> adjacent = findAdj(-1, curr.tunnelTo);
			int i = 0; 
			while(i < adjacent.size() && found == false){
				found = searchMaze(maze, adjacent.get(i), curr.tunnelTo.neigh[adjacent.get(i)], target);
				i++;
			}
		}
		// try to search down any and all available paths
		else{
			//find directions for next possible routes
			ArrayList<Integer> adjacent = findAdj(dir, curr);

			int i = 0; 
			while(i < adjacent.size() && found == false){
				found = searchMaze(maze, adjacent.get(i), curr.neigh[adjacent.get(i)], target);
				i++;
			}
		}

		return found;
	}

	public ArrayList<Integer> findAdj(int prevDir, Cell curr){
		//check if there are walls that don't exist
		ArrayList<Integer> nextDirs = new ArrayList<Integer>();
		for(int i = 0; i < dirs.length; i++){
			if (prevDir == -1){
				if (curr.wall[dirs[i]].present == false){
					nextDirs.add(dirs[i]);
				}
			}
			else{
				if (curr.wall[dirs[i]].present == false && oDirs[prevDir] != dirs[i]){
					nextDirs.add(dirs[i]);
				}
			}
		}

		if(nextDirs.size() > 1){
			for (int j = nextDirs.size() - 1; j > 0; j--){
				int idx = rand.nextInt(j + 1);
				int dir = nextDirs.get(idx);
				nextDirs.set(idx, nextDirs.get(j));
				nextDirs.set(j, dir); 
	 		}
		}

		return nextDirs;		
	}

	@Override
	public boolean isSolved() {
		// TODO Auto-generated method stub
		return solution;
	} // end if isSolved()


	@Override
	public int cellsExplored() {
		// TODO Auto-generated method stub
		return counter;
	} // end of cellsExplored()

} // end of class RecursiveBackTrackerSolver
