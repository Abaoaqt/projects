package mazeGenerator;

import maze.Maze;
import java.util.*;
import maze.Cell;

public class KruskalGenerator implements MazeGenerator {
	public ArrayList<Edge> edges;
	public ArrayList<ArrayList<Cell> > cellSets;
	public Random rand = new Random(System.currentTimeMillis());

	@Override
	public void generateMaze(Maze maze) {
		cellSets = getCellSets(maze);
		edges = generateEdges(maze);

		// pick a random edge
		// if the two cells are disjoint, remove the wall and connect their sets
		for (int i = edges.size()-1; i >= 0; i--){
			//System.out.println("edge between (" + edges.get(i).cellA.c + ", " + edges.get(i).cellA.r + ") and (" + edges.get(i).cellB.c + ", " + edges.get(i).cellB.r + ")");			
			joinSets(edges.get(i), maze);
			edges.remove(i);
		}
		//System.out.println("Total number of sets: " + cellSets.size());

	} // end of generateMaze()

	// AL of ALs to hold all cells and manage sets
	public ArrayList<ArrayList<Cell> > getCellSets(Maze maze){
		ArrayList<ArrayList<Cell> > al = new ArrayList<ArrayList<Cell> >(maze.sizeR * maze.sizeC); 

		for (int i = 0; i < maze.sizeR; i++){
			for (int j = 0; j < maze.sizeC; j++){
				ArrayList<Cell> c = new ArrayList<Cell>();
				c.add(maze.map[i][j]);
				al.add(c);
			}
		}

		//add tunnelpairs to the same set
		//search through all sets and find cells with a tunnel, if there is, add the tunnelpair to the set and delete the other set
		ArrayList<ArrayList<Cell> > toDel = new ArrayList<ArrayList<Cell> >();
		for(int s = 0; s < al.size(); s++){
			if(al.get(s) != null && al.get(s).get(0).tunnelTo != null){
				Cell jump = al.get(s).get(0).tunnelTo;
				al.get(s).add(jump);

				al.set((maze.sizeR * jump.r + jump.c), null);
			}
		}

		for (int s = 0; s < al.size(); s++){
			if(al.get(s) == null){
				al.remove(s);
			}
		}
		return al;
	}

	public ArrayList<Edge> generateEdges(Maze maze){
		int size = (2 * maze.sizeR * maze.sizeC) - maze.sizeR - maze.sizeC;
		int pos = 0;
		ArrayList<Edge> e = new ArrayList<Edge>(size);

		for (int i = 0; i < maze.sizeR; i++){
			for (int j = 0; j < maze.sizeC; j++){
				//add edges for horizontally adjacent cells
				if (j > 0){
					Edge edge = new Edge(maze.map[i][j-1], maze.map[i][j], maze.EAST);
					e.add(edge);
				}

				// add edges for vertically adjacent cells
				if (i > 0){
					Edge edge = new Edge(maze.map[i-1][j], maze.map[i][j], maze.NORTH);
					e.add(edge);
				}
			}
		}

		// randomizing edge order
		for (int i = e.size() - 1; i > 0; i--){
			int idx = rand.nextInt(i + 1);
			Edge ed = e.get(idx);
			e.set(idx, e.get(i));
			e.set(i, ed); 
 		}

		return e;
	}

	public boolean checkJoined(Edge edge){
		//if cellA and cellB are in the same set, return true else false
		boolean val = false;
		int i = 0;
		while (i < cellSets.size()){
			if(cellSets.get(i).contains(edge.cellA)){
				//System.out.println("cell A found in set " + i);
				if(cellSets.get(i).contains(edge.cellB)){
					//System.out.println("cell B found in set " + i);
					val = true;
				}
			}
			
			i++;
		}
		return val;
	}


	public void joinSets(Edge edge, Maze maze){
		int aIdx = -1;
		int bIdx = -1;
		int i = 0;
		while (i < cellSets.size() && (aIdx == -1 || bIdx == -1)){
			// find set that contains cellA
			if(cellSets.get(i).contains(edge.cellA)){
				aIdx = i;
			}
			// find set that contains cellB
			if(cellSets.get(i).contains(edge.cellB)){
				bIdx = i;
			}
			i++;
		}

		//System.out.println("A in set" + aIdx + ", B in set" + bIdx);
		// add all elements of set containing cellB to set containing cellA
		//delete set containing cell B
		if(aIdx != bIdx){
			//System.out.println("set joined");
			cellSets.get(aIdx).addAll(cellSets.get(bIdx));
			cellSets.remove(bIdx);

			//remove the walls
			maze.map[edge.cellA.r][edge.cellA.c].wall[edge.dirAToB].present = false;
			maze.map[edge.cellB.r][edge.cellB.c].wall[maze.oppoDir[edge.dirAToB]].present = false;
		}
	}
} // end of class KruskalGenerator

// edge object that contains the cell objects for edge it provides
class Edge{
	public Cell cellA;
	public Cell cellB;
	//direction cell B is wrt cell A
	public int dirAToB;

	public Edge(Cell cell1, Cell cell2, int dir){
		cellA = cell1;
		cellB = cell2;
		dirAToB = dir;
	}
}
