import java.io.PrintWriter;


/**
 * Sequential Tree Representation implementation for the {@link BSPTree} interface.
 * <p>
 * Your task is to complete the implementation of this class.
 * You may add methods, but ensure your modified class compiles and runs.
 *
 * @author Jeffrey Chan, 2016.
 * @author Yongli Ren, 2019.
 */

public class SequentialRepresentation<T> implements BSPTree<T> {
    int nonExistent = -1;
    int root = 0;
    private T[] array = (T[]) new Object[1];
    /**
     * Constructs empty graph.
     */
    public SequentialRepresentation() {
    } // end of SequentialRepresentation()

    @Override
    public void setRootNode(T nodeLabel) {
        // Implement me!
        array[root] = nodeLabel;
    } // end of setRootNode()

    @Override
    public void splitNode(T srcLabel, T leftChild, T rightChild) {
        int src = compare(root, srcLabel);
        // expand the array to fit the new nodes
        if (array.length < 2 * (src + 1)){
            expandArray( 2 * (src + 1) + 1);
        }

        // add the nodes to their respective indexes
        // left -> (2*Parent) -1
        // right -> (2 * Parent + 1) -1  
        array[2 * (src + 1) - 1] = leftChild;
        array[2 * (src + 1)] = rightChild;
    } // end of splitNode

    @Override
    public boolean findNode(T nodeLabel) {
        // found == true, not found == false
        boolean status;

        // get the idx of the node label (-1 if it doesn't exist)
        int idx = compare(root, nodeLabel);

        if (idx == nonExistent){
            status = false;
        }
        else{
            status = true;
        }
        return status;
    } // end of findNode

    @Override
    public String findParent(T nodeLabel) {
        String child = (String) nodeLabel;
        String nParent = " ";

        // search the tree for the nodelabel
        int idx = compare(root, nodeLabel);

        // node exists in the tree and the index is even -> rhs child
        if (idx != nonExistent && idx % 2 == 0){
            nParent += (String) array[idx/2];
        }
        // node exists in the tree and the index is odd -> lhs child
        else if (idx != nonExistent && idx % 2 == 1){
            nParent += (String) array[(idx-1)/2];
        }

        return child + nParent;
    } // end of findParent

    @Override
    public String findChildren(T nodeLabel) {
        String output;
        String parent;
        String lChild = " ";
        String rChild = " ";

        // gets the index of the parent node
        int pIdx = compare(root, nodeLabel);

        parent = (String) array[pIdx];

        if (2 * (pIdx + 1) < array.length){
            if (array[2 * (pIdx + 1)] != null){
                rChild = (String) array[2 * (pIdx + 1)];
            }

            if (array[2 * (pIdx + 1) - 1] != null){
                lChild = (String) array[2 * (pIdx + 1) - 1];
            }
        }

        output = parent + " " + lChild + " " + rChild;
        return output;

    } // end of findParent

    @Override
    public void printInPreorder(PrintWriter writer) {
        // start at an existing root node
        if (array[root] != null){
            writer.print(array[root] + " ");
            preOrderTraversal(root, writer);
        }
        writer.println();

    } // end of printInPreorder-*

    @Override
    public void printInInorder(PrintWriter writer) {
        // ensure that the root exists
        if (array[root] != null){
            inOrderTraversal(root, writer);
        }
        writer.println();

    } // end of printInInorder

    @Override
    public void printInPostorder(PrintWriter writer) {
        // Implement me!
        if (array[root] != null){
            postOrderTraversal(root, writer);
        }
        writer.println();
    } // end of printInPostorder

    // compares the value of the array at the index specified and then traverses the tree 
    // fix
    public int compare(int idx, T nodeLabel){
        int toReturn = nonExistent;
        for (int i = 0; i < array.length; i++){
            if (array[i].equals(nodeLabel)){
                toReturn = i;
            }
        }
        return toReturn;
        
    }

    // grow the array to fit new children nodes
    public void expandArray(int newSize){
        T[] tArray = (T[]) new Object[newSize];
        for (int i = 0; i < array.length; i++){
            tArray[i] = array[i];
        }

        array = tArray;
    }

    // move through the tree in pre-order
    public void preOrderTraversal(int parentIdx, PrintWriter writer){
        // check that the left child exists and then recursively traverse that subtree
        int leftIdx =  2 * (parentIdx + 1) - 1;
        if (leftIdx < array.length && array[leftIdx] != null){
            writer.print(array[leftIdx] + " ");
            preOrderTraversal(leftIdx, writer);
        }

        // check that the right child exists and then recursively traverse that subtree
        int rightIdx = 2 * (parentIdx + 1);
        if (rightIdx < array.length && array[rightIdx] != null){
            writer.print(array[rightIdx] + " ");
            preOrderTraversal(rightIdx, writer);
        }
    }

    public void inOrderTraversal(int parentIdx, PrintWriter writer){
        // travel down the LHS while there are children nodes
        int leftIdx =  2 * (parentIdx + 1) - 1;
        if (leftIdx < array.length && array[leftIdx] != null){
            inOrderTraversal(leftIdx, writer);
        }
        // once there are no more down LHS print this nodelabel
        writer.print(array[parentIdx] + " ");

        // travel down the RHS while there are children nodes
        int rightIdx =  2 * (parentIdx + 1);
        if (rightIdx < array.length && array[rightIdx] != null){
            inOrderTraversal(rightIdx, writer);
        }
    }

    public void postOrderTraversal(int parentIdx, PrintWriter writer){
        // travel down the LHS while there are children nodes
        int leftIdx =  2 * (parentIdx + 1) - 1;
        if (leftIdx < array.length && array[leftIdx] != null){
            postOrderTraversal(leftIdx, writer);
        }

        // travel down the RHS while there are children node
        int rightIdx =  2 * (parentIdx + 1);
        if (rightIdx < array.length && array[rightIdx] != null){
            postOrderTraversal(rightIdx, writer);
        }

        // if there are no more nodes to visit then print the label of this node
        writer.print(array[parentIdx] + " ");

    }

} // end of class SequentialRepresentation