# 8-Digits-Puzzle
## Introduce
This is a puzzle mentioned in the Artifitial Intelligence course, written in C and with a lot of improvements to be added.

## Basic Idea
We use a search tree model in this program. At first, we generate the tree root with the assigned board situation, and 
then we generate its child nodes, put them into the 'open' space (which is actually a stack defined in `struct.h`). Then 
we sort the 'open' space, making the child nodes with lower value to be popped out first.After the generation, the root 
node is put into the 'close' space, which has the same data structure as 'open'.  

After doing this, we pop a child node from the 'open' space, generating its child nodes while sorting them, and put it 
into the 'close' space again. We go on this loop util we get a node whose value equals to its level. By this means, we 
find the desired node.  

We then put the node into a new space called 'record', and push all its ancestor nodes into it. We display our output by 
popping the nodes out from 'record'. By this means the result is in the right order.  

**Attention** It is important to know that not all input situations will have its result. Many of the situations, as they 
are somewhat complicated, have problems finding the solution. This problem gets more complex as the necessary steps 
increases.  

## Additional Information
This program is originally based on the algorithm mentioned in my Artificial Intelligence Introduction course. As my teacher 
gave the basic idea of it, I write it in C language. It is a work roughly cost me 2 days and thus contains a lot of problems. 
In my next commit, I will try to add some features to improve it. 
