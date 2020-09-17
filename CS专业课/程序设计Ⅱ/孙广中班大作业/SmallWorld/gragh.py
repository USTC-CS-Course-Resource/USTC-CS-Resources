import sys
import stdio
from instream import InStream


# -----------------------------------------------------------------------

class Graph:

    # Construct a new Graph object. If a filename is specified,
    # populate the Graph object by reading data from the specified
    # file with the specified delimiter.
    def __init__(self, filename=None, delimiter=None):
        self._e = 0
        self._adj = dict()
        if filename is not None:
            instream = InStream(filename)
            while instream.hasNextLine():
                line = instream.readLine()
                names = line.split(delimiter)
                for i in range(1, len(names)):
                    self.addEdge(names[0], names[i])

    # Add an edge to self between vertex v and vertex w.
    def addEdge(self, v, w):
        if not self.hasVertex(v): self._adj[v] = set()
        if not self.hasVertex(w): self._adj[w] = set()
        if not self.hasEdge(v, w):
            self._e += 1
            self._adj[v].add(w)
            self._adj[w].add(v)

    # Return an iterable collection containing all neighbors of
    # vertex v in self.
    def adjacentTo(self, v):
        return iter(self._adj[v])

    # Return an iterable collection of all vertices in self.
    def vertices(self):
        return iter(self._adj)

    # Return True if vertex v is in self, and False otherwise.
    def hasVertex(self, v):
        return v in self._adj

    # Return True if v-w is an edge in self, and False otherwise.
    def hasEdge(self, v, w):
        return w in self._adj[v]

    # Return the number of vertices in self.
    def countV(self):
        return len(self._adj)

    # Return the number of edges in self.
    def countE(self):
        return self._e

    # Return the degree of vertex v of self.
    def degree(self, v):
        return len(self._adj[v])

    # Return a string representation of self.
    def __str__(self):
        s = ''
        for v in self.vertices():
            s += v + '  '
            for w in self.adjacentTo(v):
                s += w + ' '
            s += '\n'
        return s


# -----------------------------------------------------------------------

# For testing. Accept string file as a command-line argument. Create a
# Graph object by reading from file. Write the Graph object to standard
# output.

def main():
    file = sys.argv[1]
    graph = Graph(file)
    stdio.writeln(graph)


if __name__ == '__main__':
    main()

# -----------------------------------------------------------------------

# python graph.py tinygraph.txt
# A  G H B C
# G  A C
# H  A B
# B  A H C
# C  A G B

