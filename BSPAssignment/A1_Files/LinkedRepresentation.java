import java.io.PrintWriter;


/**
 * Linked Tree Representation implementation for the {@link BSPTree} interface.
 * <p>
 * Your task is to complete the implementation of this class.
 * You may add methods, but ensure your modified class compiles and runs.
 *
 * @author Jeffrey Chan, 2016. 
 * @author Yongli Ren, 2019.
 */

public class LinkedRepresentation<T> implements BSPTree<T> {

    private Node root;
    /**
     * Constructs empty tree.
     */
    public LinkedRepresentation() {
        // Implement me!
    } // end of LinkedRepresentation()

    @Override
    public void setRootNode(T nodeLabel) {
        root = new Node(null, nodeLabel);
    } // end of setRootNode()

    @Override
    public void splitNode(T srcLabel, T leftChild, T rightChild) {
        addChildNodes(root, srcLabel, leftChild, rightChild);

    } // end of splitNode

    @Override
    public boolean findNode(T nodeLabel) {
        boolean result;
        Node fNode = compare(root, nodeLabel);
        //if compare returns null, then the nodeLabel doesnt exist in the tree
        if (fNode == null){
            result = false;
        }
        // if fNode contains a node object, then the node has been located
        else{
            result = true;
        }
        return result;
    } // end of findNode

    @Override
    public String findParent(T nodeLabel) {
        // Implement me!
        String msg = "";
        // find the node that matches the input value
        Node child = compare(root, nodeLabel);
        if (child != null){
            // conjoin the node value and the value of the parent
            msg = (String) nodeLabel + " ";

            Node parent = child.getParent();
            if (parent != null){
                msg += (String) parent.getValue();
            }
        }

        return msg;
    } // end of findParent

    @Override
    public String findChildren(T nodeLabel) {
        // Implement me!
        String msg = "";
        // find the parent node
        Node parent = compare(root, nodeLabel);

        if (parent != null){
            // if the parent exists 
            msg = (String) nodeLabel;

            // if the parent has children
            if (parent.hasChildren()){
                msg += " " + (String) parent.getLChild().getValue() + " " + (String) parent.getRChild().getValue();             
            }
        }

        return msg;
    } // end of findParent

    @Override
    public void printInPreorder(PrintWriter writer) {
        // travese the tree starting from the root node
        if (root != null){
            preOrderTraversal(root, writer);
        }
    } // end of printInPreorder

    @Override
    public void printInInorder(PrintWriter writer) {
        if (root != null){
            inOrderTraversal(root, writer);
        }
    } // end of printInInorder

    @Override
    public void printInPostorder(PrintWriter writer) {
        if (root != null){
            postOrderTraversal(root, writer);
        }
    } // end of printInPostorder

    public Node compare(Node curr, T nodeLabel){
        Node found = null;
        // set found to the current node if the values are equal
        if (curr.getValue().equals(nodeLabel)){
            found = curr;
        }
        // if the current node isn't equal then check the left subtree and then the right subtree
        else if (curr.hasChildren()){
            found = compare(curr.getLChild(), nodeLabel);

            // if the node still hasn't been found then check the right subtree
            if (found == null){
                found = compare(curr.getRChild(), nodeLabel);
            }
        }

        return found;

    }
    public boolean addChildNodes( Node curr, T srcLabel, T leftChild, T rightChild){
        boolean cSet = false;
        // set found to the current node if the values are equal
        if (curr.getValue().equals(srcLabel)){
            curr.addChildren(leftChild, rightChild);
            cSet = true;
        }
        // if the current node isn't equal then check the left subtree and then the right subtree
        else if (curr.hasChildren()){
            cSet = addChildNodes(curr.getLChild(), srcLabel, leftChild, rightChild);

            // if the node still hasn't been found then check the right subtree
            if (cSet == false){
                cSet = addChildNodes(curr.getRChild(), srcLabel, leftChild, rightChild);
            }
        }

        return cSet;

    }

    public void preOrderTraversal(Node curr, PrintWriter writer){
        //print the parent value
        writer.print((String) curr.getValue() + " ");

        // check that the current node has children
        if (curr.hasChildren()){
            // first traverse recursively down the left subtree
            preOrderTraversal(curr.getLChild(), writer);

            // ten traverse down the right subtree
            preOrderTraversal(curr.getRChild(), writer);
        }
    }

    public void inOrderTraversal(Node curr, PrintWriter writer){
        if (curr.hasChildren()){
            // traverse the left subtree before printin
            inOrderTraversal(curr.getLChild(), writer);

            // print the current node value
            writer.print((String) curr.getValue() + " ");

            // traverse the right subtree
            inOrderTraversal(curr.getRChild(), writer);
        }
        // if there are no children just print the node value
        else{
            writer.print((String) curr.getValue() + " ");
        }
    }

    public void postOrderTraversal(Node curr, PrintWriter writer){
        if (curr.hasChildren()){
            // traverse the left subtree before printing
            postOrderTraversal(curr.getLChild(), writer);

            // traverse the right subtree
            postOrderTraversal(curr.getRChild(), writer);
        }
        // print if there are no children or the subtrees have been traversed
        writer.print((String) curr.getValue() + " ");
    }

} // end of class LinkedRepresentation

class Node<T>{
    private T value;
    private Node parent;
    private Node lChild = null;
    private Node rChild = null;
    private boolean hasC;

    public Node(Node  parent, T val){
        this.parent = parent;
        value = val;
        hasC = false;
    }

    public void addChildren(T lVal, T rVal){
        lChild = new Node(this, lVal);
        rChild = new Node(this, rVal);
        hasC = true;
    }

    public Node getLChild(){
        return lChild;
    }

    public Node getRChild(){
        return rChild;
    }

    public boolean hasChildren(){
        return hasC;
    }

    public T getValue(){
        return value;
    }

    public Node getParent(){
        return parent;
    }

}