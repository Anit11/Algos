/*
tree* findLCA(tree* root, tree* a, tree* b)
bool isTreeBalanced(tree* root)
uint32_t computeHeight(tree* root)
int countTree(int numNodes)
bool sameTree(tree* a, tree* b)
void doubleTree(tree* root)
void mirror(tree* root)
void printPathsVec(tree* root)
void printPathsRecurVec(tree* root, vector<int> path)
void printVector(vector<int> path)
void printPaths(tree* root)
void printPathsRecur(tree* root, int path[], int pathLen)
void printArray(int path[], int len)
bool hasPathSum(tree* root, int sum)
int minValue(tree* root)
int maxDepth(tree* root)
int size(tree* root)
tree* build123()
tree* insert(tree* root, int data)
void printTree(tree* root)
*/

// This contains solution to Stanford's Tree problems.
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <unordered_map>
using namespace std;

struct tree
{
    int data;
    struct tree* left;
    struct tree* right;
};

tree* newNode(int data)
{
    struct tree* node = new tree();
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void printTree(tree* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        cout << root->data << "  ";
        printTree(root->left);
        printTree(root->right);
    }
}

void printTreeInorder(tree* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        printTreeInorder(root->left);
        cout << root->data << "  ";
        printTreeInorder(root->right);
    }
}

tree* insert(tree* root, int data)
{
    if (root == NULL)
    {
        return newNode(data);
    }
    else
    {
        if (data > root->data)
        {
            root->right = insert(root->right, data);
        }
        else
        {
            root->left = insert(root->left, data);
        }
    }

    return root;
}

tree* build123()
{
    struct tree* root = NULL;

    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 6);

    return root;
}

// ------------------------------------------------------------------------------------------------
// Problem 1.
//      Compute the Number of nodes in the tree
// ------------------------------------------------------------------------------------------------
int size(tree* root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (size(root->left) + 1 + size(root->right));
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 2.
//      Compute the max depth in the tree
// ------------------------------------------------------------------------------------------------
int maxDepth(tree* root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int lDepth = 1 + maxDepth(root->left);
        int yDepth = 1 + maxDepth(root->right);
        return (lDepth > yDepth ? lDepth : yDepth);
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 3.
//      Compute the minimum value
// ------------------------------------------------------------------------------------------------
int minValue(tree* root)
{
    while (root != NULL)
    {
        if (root->left == NULL)
        {
            return root->data;
        }
        return minValue(root->left);
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 4.
//      Compute if there is path that matches the sum
// ------------------------------------------------------------------------------------------------
bool hasPathSum(tree* root, int sum)
{
    if (root == NULL)
    {
        return false;
    }
    else if (root->left == NULL && root->right == NULL && sum == root->data)
    {
        return true;
    }
    else if (root->left != NULL || root->right != NULL)
    {
        return (hasPathSum(root->left, sum - root->data) ||
                hasPathSum(root->right, sum - root->data));
    }
    else
    {
        return false;
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 5.
//      Compute the Paths recursively
// ------------------------------------------------------------------------------------------------
void printArray(int path[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << path[i] << "  ";
    }
    cout << endl;
}

void printPathsRecur(tree* root, int path[], int pathLen)
{
    if (root == NULL)
    {
        cout << endl;
        return;
    }
    else if (root->left == NULL && root->right==NULL)
    {
        path[pathLen] = root->data;
        printArray(path, pathLen+1);
        return;
    }
    else
    {
        path[pathLen] = root->data;
        printPathsRecur(root->left, path, pathLen+1);
        printPathsRecur(root->right, path, pathLen+1);
    }
}

void printPaths(tree* root)
{
    int path[1000];
    printPathsRecur(root, path, 0);
}

// ------------------------------------------------------------------------------------------------
// Problem 6.
//      Compute the paths using vector
// ------------------------------------------------------------------------------------------------
// Using Vectors to print the path
void printVector(vector<int> path)
{
    for (vector<int>::iterator it = path.begin(); it != path.end(); it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
}

void printPathsRecurVec(tree* root, vector<int> path)
{
    if (root == NULL)
    {
        cout << endl;
        return;
    }
    else if (root->left == NULL && root->right==NULL)
    {
        path.push_back(root->data);
        printVector(path);
        return;
    }
    else
    {
        path.push_back(root->data);
        printPathsRecurVec(root->left, path);
        printPathsRecurVec(root->right, path);
    }

}

void printPathsVec(tree* root)
{
    vector<int> vPath;
    printPathsRecurVec(root, vPath);
}

// ------------------------------------------------------------------------------------------------
// Problem 7.
//      Compute the mirror of a tree
// ------------------------------------------------------------------------------------------------
void mirror(tree* root)
{
    if (root == NULL)
    {
        return;
    }

    mirror(root->left);
    mirror(root->right);

    tree* temp = root->left;
    root->left = root->right;
    root->right = temp;
}

// ------------------------------------------------------------------------------------------------
// Problem 8.
//      Compute the double of a tree
// ------------------------------------------------------------------------------------------------
void doubleTree(tree* root)
{
    if (root == NULL)
    {
        return;
    }

    // Copy the left and right of current node
    tree* tmpL = root->left;
    tree* tmpR = root->right;

    tree* temp = new tree();
    temp->data = root->data;
    temp->left = root->left;
    temp->right = NULL;

    // Add the new node to the left of temp.
    root->left = temp;

    doubleTree(tmpL);
    doubleTree(tmpR);
}

// ------------------------------------------------------------------------------------------------
// Problem 9.
//      Compute if two trees are same
// ------------------------------------------------------------------------------------------------
bool sameTree(tree* a, tree* b)
{
    if (a == NULL && b == NULL)
    {
        return true;
    }
    else if (a == NULL && b != NULL)
    {
        return false;
    }
    else if (a != NULL && b == NULL)
    {
        return false;
    }
    else if (a->data != b->data)
    {
        return false;
    }
    else
    {
        // a's data is same as b's data. Procced to child trees
        return (sameTree(a->left, b->left) &&
                sameTree(a->right, b->right));
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 10.
//      Count the number of possible trees
// ------------------------------------------------------------------------------------------------
int countTree(int numNodes)
{
    if (numNodes == 0 || numNodes == 1)
    {
        return numNodes;
    }
    return (countTree(numNodes-1) + countTree(numNodes-1));
    return (1 + countTree(numNodes-1));
}

// ------------------------------------------------------------------------------------------------
// Problem 11.
//      Compute the max height of a tree
// ------------------------------------------------------------------------------------------------
// This functions computes the height of a tree.
uint32_t computeHeight(tree* root)
{
    if (root != NULL)
    {
        return 0;
    }

    uint32_t leftHeight = 1 + computeHeight(root->left);
    uint32_t rightHeight = 1 + computeHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// ------------------------------------------------------------------------------------------------
// Problem 12.
// http://stackoverflow.com/questions/742844/how-to-determine-if-binary-tree-is-balanced
// This tell if a binary tree is Balanced or not.
// VERY IMP: What if the tree is highly unbalanced with million nodes on one side
// and very few nodes on other side.
// ------------------------------------------------------------------------------------------------
bool isTreeBalanced(tree* root)
{
    return ((root == NULL) ||
            ((isTreeBalanced(root->left)) &&
            (isTreeBalanced(root->right)) &&
            (abs(computeHeight(root->left) - computeHeight(root->right)) <= 1)));
}

// ------------------------------------------------------------------------------------------------
// Problem 13.
//      Compute the LCA of a tree
// This function ASSUMES that node a and node b are present in the Tree
// ------------------------------------------------------------------------------------------------
tree* findLCA(tree* root, tree* a, tree* b)
{
    cout << "0. Root: " << root << " ; a: " << a << " ; b: " << b << endl;
    if (root == NULL)
    {
        //cout << "1. " << endl;
        return NULL;
    }

    // IMP: This doesnot cover the following edge case.
    // When either is the direct child of other. 
    /*
    if ((root->left == a && root->right == b) ||
        (root->left == b && root->right == a))
    {
        return root;
    }
    */

    // Fix for the above problem
    if (root == a || root == b)
    {
        //cout << "2. " << endl;
        return root;
    }

    tree* la = findLCA(root->left, a, b);
    tree* ra = findLCA(root->right, a, b);

    if (la != NULL && ra != NULL)
    {
        //cout << "3. " << endl;
        return root;
    }

    else if (la != NULL)
    {
        //cout << "4. " << endl;
        return la;
    }
    else
    {
        //cout << "5. " << endl;
        return ra;
    }
}

int findLCANum(tree* root)
{
    tree* result = new tree();

    result = findLCA(root, root, root);
    //result = findLCA(root, root->right->right->left, root->left);
    return result->data;
}

// ------------------------------------------------------------------------------------------------
// Problem 14
// http://www.geeksforgeeks.org/find-the-maximum-sum-path-in-a-binary-tree/
//
//  Given a Binary Tree, find the maximum sum path from a leaf to root.
//  For example, in the following tree, there are three leaf to root paths 8->-2->10, -4->-2->10 and 7->10.
//  The sums of these three paths are 16, 4 and 17 respectively.
//  The maximum of them is 17 and the path for maximum is 7->10.
// ------------------------------------------------------------------------------------------------
void maxSumLeafToRootPath(tree* root, int& curSum, int& maxSum)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        curSum += root->data;
        if (curSum > maxSum)
        {
            maxSum = curSum;
        }

        // IMP: Reset Current sum to Previous value
        curSum -= root->data;

        return;
    }

    // http://stackoverflow.com/questions/16767345/invalid-initialization-of-non-const-reference-of-type-int-from-a-temporary-of
    // VERY IMP: Can't pass a VALUE directly to a reference. It should be put in a 
    // variable before doing so.
    int temp = root->data + curSum;
    maxSumLeafToRootPath(root->left, temp, maxSum);
    maxSumLeafToRootPath(root->right, temp, maxSum);
}

int maxSumLeafToRoot(tree* root)
{
    int maxSum = 0;
    int curSum = 0;
    maxSumLeafToRootPath(root, curSum, maxSum);

    return maxSum;
}

// ------------------------------------------------------------------------------------------------
// Problem 15
// http://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/
//
//  Given a Binary Tree, find the maximum sum path from a leaf to leaf.
//  maxLeafToLeaf - Store the max leaf to leaf value- Max Sum stored between two leaves.
//  returValue - Return the max value from that node to its leaves.
//
//  IMP:
//  We are interested in TWO MAIN thins.
//  1. Given a Root, what is the sum of ROOT + LEFT CHILD + RIGHT CHILD
//  2. ROOT + MAX (LEFT CHILD, RIGHT CHILD)
//  3. If ROOT is one sided return INTMIN
//
//  (1) Will give if root, left, right hold the MAX sum
//  (2) Will give if ROOT + (LEFT OR RIGHT) is a part of the MAX sum
// ------------------------------------------------------------------------------------------------
int maxSumLeafToLeafRec(tree* root, int& maxLeafToLeaf)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->left == NULL && root->right == NULL)
    {
        return root->data;
    }

    int leftMaxSum = maxSumLeafToLeafRec(root->left, maxLeafToLeaf);
    int rightMaxSum = maxSumLeafToLeafRec(root->right, maxLeafToLeaf);

    if (root->left != NULL && root->right != NULL)
    {
        maxLeafToLeaf = max(maxLeafToLeaf, leftMaxSum + rightMaxSum + root->data);

        // Return the max value from current node to its leaves
        return (max(leftMaxSum, rightMaxSum) + root->data);
    }

    if (root->left != NULL)
    {

        return leftMaxSum + root->data;
    }
    else
    {
        return rightMaxSum + root->data;
    }
}

int maxSumLeafToLeaf(tree* root)
{
    int maxSum = INT_MIN;

    // We don't need the return value here
    maxSumLeafToLeafRec(root, maxSum);
    return maxSum;
}

// ------------------------------------------------------------------------------------------------
// Problem 16
// http://www.geeksforgeeks.org/find-maximum-path-sum-in-a-binary-tree/
//
//  Given a Binary Tree, find the maximum sum path from a ANY NODE to ANY NODE
//  maxSum - Contains the max sum found till now
//  returValue - Return the max value from that node to its leaves.
//
//  MaxSum can either of the following
//      a. root->data
//      b. root->data + leftSum
//      c. root->data + rightSum
//      d. root->data + leftSum + rightSum
//
//  IMP:
//  We are interested in TWO MAIN things.
//  1. We should return MAX found along LEFT OR RIGHT side
//  2. MaxSum will store the actual Max got from LEFT OR RIGHT OR BOTH
// ------------------------------------------------------------------------------------------------
int maxSumNodeToNodeRec(tree* root, int& maxSum)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->left == NULL && root->right == NULL)
    {
        return root->data;
    }

    int leftMaxSum = maxSumNodeToNodeRec(root->left, maxSum);
    int rightMaxSum = maxSumNodeToNodeRec(root->right, maxSum);

    // We will RETURN the Max value that will belong to either side.
    //      root + leftMax OR root + rightMax OR root
    //      This values gets returned so that OTHER nodes can use this info.
    //
    // We compute the Total Max and store it in MAX SUM.
    int tmp1 = max(root->data, max(leftMaxSum, rightMaxSum) + root->data);
    maxSum = max(maxSum, max(tmp1, leftMaxSum + root->data + rightMaxSum));
    
    return tmp1;
}

int maxSumNodeToNode(tree* root)
{
    if (root == NULL)
    {
        return 0;
    }

    int maxSum = 0;

    // We don't need the return value here
    maxSumNodeToNodeRec(root, maxSum);
    return maxSum;
}

// ------------------------------------------------------------------------------------------------
// Problem 17
// http://stackoverflow.com/questions/17703952/print-the-longest-leaf-to-leaf-path-in-a-binary-tree-and-its-length
//
// Imagine a tree like below
//              a
//            b  
//          c   f
//        d       g
//      e          
//
// That is why there is another wrapper function to determine if the final max is 
// MaxPathLen OR the returned value which is MaxAlongOneSide
// ------------------------------------------------------------------------------------------------
uint32_t longestPathLengthRec(tree* root, uint32_t& maxPathLen)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }

    uint32_t leftPathLen = longestPathLengthRec(root->left, maxPathLen);
    uint32_t rightPathLen = longestPathLengthRec(root->right, maxPathLen);

    uint32_t maxAlongOneSide = 1 + max(leftPathLen, rightPathLen);

    // This is the total max path len by considering both sides as well
    maxPathLen = max(maxPathLen, max(maxAlongOneSide, 1 + leftPathLen + rightPathLen));

    return maxAlongOneSide;
}

uint32_t longPathLength(tree* root)
{
    if (root == NULL)
    {
        return 0;
    }

    uint32_t maxPathLen = 0;
    uint32_t maxAlongOneSide = longestPathLengthRec(root, maxPathLen);

    return max(maxPathLen, maxAlongOneSide);

}

// ------------------------------------------------------------------------------------------------
// Problem 18
//      Find the nearest element that is lesser than the given key
// ------------------------------------------------------------------------------------------------
int nearestLesserElmt(tree* root, int key, int& minElmt)
{
    if (root == NULL)
    {
        return INT_MAX;
    }

    if (root->data == key)
    {
        if (root->left != NULL)
        {
            // If both are present return the number that is JUST smaller than key.
            // So larger of the two minimum numbers
            return max(minElmt, root->left->data);
        }
        return minElmt;
    }

    if (key > root->data)
    {
        minElmt = root->data;
        return nearestLesserElmt(root->right, key, minElmt);
    }
    else
    {
        return nearestLesserElmt(root->left, key, minElmt);
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 19
//      Print Tree in Level Order
// ------------------------------------------------------------------------------------------------
void printTreeLevelOrder(tree* root)
{
    if (root == NULL)
    {
        return;
    }

    queue<tree*> lvlQueue;
    lvlQueue.push(root);
    uint32_t levelCount = 1;
    uint32_t nextLvlCnt = 0;

    while(!lvlQueue.empty())
    {
        tree* temp = lvlQueue.front();
        lvlQueue.pop();
        levelCount--;
        cout << temp->data << " ";

        if (temp->left != NULL)
        {
            lvlQueue.push(temp->left);
            nextLvlCnt++;
        }

        if (temp->right != NULL)
        {
            lvlQueue.push(temp->right);
            nextLvlCnt++;
        }

        if (levelCount == 0)
        {
            cout << endl;
            levelCount = nextLvlCnt;
            nextLvlCnt = 0;
        }
    }
}


// ------------------------------------------------------------------------------------------------
// Problem 20
//      Print Tree in Spiral Order
// ------------------------------------------------------------------------------------------------
void printSpiralOrder(tree* root)
{
    if (root == NULL)
    {
        return;
    }

    if (root -> left == NULL && root -> right == NULL)
    {
        cout << root->data << endl;
        return;
    }

    vector<tree*> leftStack;
    vector<tree*> rightStack;

    // To Start with put the first level in the stack
    cout << root->data << endl;
    if (root->left != NULL)
    {
        rightStack.push_back(root->left);
    }

    if (root->right != NULL)
    {
        rightStack.push_back(root->right);
    }

    while (!leftStack.empty() || !rightStack.empty())
    {
        while (!rightStack.empty())
        {
            tree* temp = rightStack.back();
            cout << temp->data << " ";

            if (temp->right != NULL)
            {
                leftStack.push_back(temp->right);
            }

            if (temp->left != NULL)
            {
                leftStack.push_back(temp->left);
            }

            rightStack.pop_back();
        }
        cout << endl;

        while (!leftStack.empty())
        {
            tree* temp = leftStack.back();
            cout << temp->data << " ";

            if (temp->left != NULL)
            {
                rightStack.push_back(temp->left);
            }

            if (temp->right != NULL)
            {
                rightStack.push_back(temp->right);
            }
            leftStack.pop_back();
        }
        cout << endl;
    }
}

// ------------------------------------------------------------------------------------------------
// Problem 21
//      Print Tree in Vertical Order
// http://stackoverflow.com/questions/14485255/vertical-sum-in-a-given-binary-tree?lq=1
// http://stackoverflow.com/questions/20521098/print-a-tree-vertically
// ------------------------------------------------------------------------------------------------
void fillHorizontalDistanceMap(tree* root, unordered_map<int, vector<int> >& horiDistMap, int horiDist)
{
    if (root == NULL)
    {
        return;
    }

    auto itr = horiDistMap.find(horiDist);
    if (itr != horiDistMap.end())
    {
        itr->second.push_back(root->data);
    }
    else
    {
        horiDistMap[horiDist] = vector<int> {root->data};
    }

    fillHorizontalDistanceMap(root->left, horiDistMap, horiDist - 1);
    fillHorizontalDistanceMap(root->right, horiDistMap, horiDist + 1);
}

void printVerticalOrder(tree* root)
{
    // This map should be finally sorted by KEYS and the printed
    unordered_map<int, vector<int> > horiDistMap;

    // Use a Map to store all Nodes's corresponding to a horizontal distance
    fillHorizontalDistanceMap(root, horiDistMap, 0);

    // Sort the Undered Map. This needs an extra data structure
    std::map<int, vector<int> > orderedDistMap(horiDistMap.begin(), horiDistMap.end());

    // Print the Map in Order
    // Get each element of the map
    // If we use for each, can't use itr->second. So using iterator to traverse.
    for (auto itr = orderedDistMap.begin(); itr != orderedDistMap.end(); itr++)
    {
        // Each element of the map is a vector of values corresponding to an horizontal
        // distance.
        cout << itr->first << ": ";
        for (auto data : itr->second)
        {
            cout << data << ", ";
        }
        cout << endl;
    }
}

// ------------------------------------------------------------------------------------------------
// Main Function
// ------------------------------------------------------------------------------------------------
int main()
{
    cout << "TREE" << endl;
    struct tree* root = NULL;
    root = build123();
    printTree(root);
    cout << endl;

    cout << "Size: " << size(root) << endl;
    cout << "Max Depth: " << maxDepth(root) << endl;
    cout << "Has Path Sum: " << hasPathSum(root, 12) << endl;
    cout << "Has Path Sum: " << hasPathSum(root, 18) << endl;
    cout << "Has Path Sum: " << hasPathSum(root, 5) << endl;

    cout << "Min Value: " << minValue(root) << endl;
    cout << "Paths: ";
    printPaths(root);

    cout << "Paths Using Vectors: ";
    printPathsVec(root);

    cout << "Mirror of a Node" << endl;
    printTree(root);
    /*
    cout << endl;
    mirror(root);
    printTree(root);
    cout << endl;

    cout << "Doubling a tree" << endl;
    doubleTree(root);
    printTree(root);
    */

    // Find LCA
    {
        cout << endl << "LCA" << endl;
        cout << findLCANum(root) << endl;
    }

    // Find Max root to leaf path
    {
        struct tree* root = newNode(-15);
        root->left = newNode(5);
        root->right = newNode(6);
        root->left->left = newNode(-8);
        root->left->right = newNode(1);
        root->left->left->left = newNode(2);
        root->left->left->right = newNode(6);
        root->right->left = newNode(3);
        root->right->right = newNode(9);
        root->right->right->right= newNode(0);
        root->right->right->right->left= newNode(4);
        root->right->right->right->right= newNode(-1);
        root->right->right->right->right->left= newNode(10);

        struct tree *root1 = newNode(10);
        root1->left	 = newNode(2);
        root1->right	 = newNode(10);
        root1->left->left = newNode(-20);
        root1->left->right = newNode(-1);
        root1->right->right = newNode(-25);
        root1->right->right->left = newNode(3);
        root1->right->right->right = newNode(4);

        printTree(root);
        cout << endl;

        printTreeInorder(root);
        cout << endl;

        cout << "Max Root to Leaf: " << maxSumLeafToRoot(root1) << endl;

        cout << "Max Leaf to Leaf: " << maxSumLeafToLeaf(root1) << endl;

        cout << "Max Node to Node: " << maxSumNodeToNode(root1) << endl;
    }

    // Max Length of Path
    {
        struct tree* root = newNode(1);
        root->left = newNode(2);
        root->left->left = newNode(3);
        root->left->right = newNode(4);
        root->left->left->left = newNode(5);
        root->left->right->right = newNode(6);
        root->left->left->left->left = newNode(7);

        cout << "Max Length of Path: " << longPathLength(root) << endl;
    }

    // Find element that is lesser and closest to a given key
    {
        int minElement = INT_MIN;

        printTree(root);
        cout << endl;

        printTreeInorder(root);
        cout << endl;


        cout << "Nearest Lower Element: " << nearestLesserElmt(root, 4, minElement) << endl;
    }

    // Problem 19,20 Print Tree in Level and Spiral Order
    {
        struct tree* root = newNode(1);
        root->left = newNode(10);
        root->right = newNode(11);

        root->left->left = newNode(100);
        root->left->right = newNode(101);
        root->right->left = newNode(102);
        root->right->right = newNode(103);


        root->left->left->left = newNode(200);
        root->left->left->right = newNode(201);
        root->left->right->left = newNode(202);
        root->left->right->right = newNode(203);
        root->right->left->left = newNode(204);
        root->right->left->right = newNode(205);
        root->right->right->left = newNode(206);
        root->right->right->right = newNode(207);

        root->left->left->left->left = newNode(300);
        root->left->left->left->right = newNode(301);
        root->left->left->right->left = newNode(302);
        root->left->left->right->right = newNode(303);


        cout << "Tree in Level Order" << endl;
        printTreeLevelOrder(root);
        cout << endl;

        cout << "Tree in Spiral Order" << endl;
        printSpiralOrder(root);
    }

    // Problem 21 Vertical Order of a Binary Tree
    {
        cout << endl << "Print Tree in Vertical Order" << endl;
        struct tree* root = newNode(1);
        root->left = newNode(10);
        root->right = newNode(11);

        root->left->left = newNode(100);
        root->left->right = newNode(101);
        root->right->left = newNode(102);
        root->right->right = newNode(103);

        printVerticalOrder(root);
    }

    cout << endl;

    return 0;
}
