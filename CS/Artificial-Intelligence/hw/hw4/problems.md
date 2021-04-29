5.9 This problem exercises the basic concepts of game playing, using tic-tac-toe (noughts and crosses) as an example. We define as the number of rows, columns, or diagonals with exactly and no . Similarly, is the number of rows, columns, or diagonals with just . The utility function assigns to any position with and to any position with . All other terminal positions have utility 0. For nonterminal positions, we use a linear evaluation function defined as

.

a. Approximately how many possible games of tic-tac-toe are there?

b. Show the whole game tree starting from an empty board down to depth 2 (i.e., one
and one

on the board), taking symmetry into account.

c. Mark on your tree the evaluations of all the positions at depth 2.

d. Using the minimax algorithm, mark on your tree the backed-up values for the positions at depths 1 and 0, and use those values to choose the best starting move.

e. Circle the nodes at depth 2 that would not be evaluated if alpha–beta pruning were applied, assuming the nodes are generated in the optimal order for alpha–beta pruning.

5.8 Consider the two-player game described in Figure 5.17.

a. Draw the complete game tree, using the following conventions:

    Write each state as 

, where and

    denote the token locations.

    Put each terminal state in a square box and write its game value in a circle.

    Put loop states (states that already appear on the path to the root) in double square boxes. Since their value is unclear, annotate each with a “?” in a circle.

b. Now mark each node with its backed-up minimax value (also in a circle). Explain how you handled the “?” values and why.

c. Explain why the standard minimax algorithm would fail on this game tree and briefly sketch how you might fix it, drawing on your answer to (b). Does your modified algorithm give optimal decisions for all games with loops?

d. This 4-square game can be generalized to n squares for any
. Prove that wins if is even and loses if

is odd.

5.13 Develop a formal proof of correctness for alpha–beta pruning. To do this, consider the situation shown in Figure 5.18. The question is whether to prune node
, which is a maxnode and a descendant of node . The basic idea is to prune it if and only if the minimax value of can be shown to be independent of the value of

.

a. Mode
takes on the minimum value among its children: . Find a similar expression for and hence an expression for in terms of

.

b. Let
be the minimum (or maximum) value of the nodes to the left of node at depth , whose minimax value is already known. Similarly, let be the minimum (or maximum) value of the unexplored nodes to the right of at depth . Rewrite your expression for in terms of the and

values.

c. Now reformulate the expression to show that in order to affect
must not exceed a certain bound derived from the

values.

d. Repeat the process for the case where
is a min-node. 