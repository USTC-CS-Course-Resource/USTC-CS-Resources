import stdio
from gragh import Graph
from linkedqueue import Queue


# PathFinder object represents paths within a specified graph from a
# specified source index.

class PathFinder:

    # Construct a PathFinder object on the specfied graph for
    # source vertex s.
    def __init__(self, graph, s):
        self._distTo = dict()
        self._edgeTo = dict()
        queue = Queue()
        queue.enqueue(s)
        self._distTo[s] = 0
        self._edgeTo[s] = None
        while not queue.isEmpty():
            v = queue.dequeue()
            for w in graph.adjacentTo(v):
                if w not in self._distTo:
                    queue.enqueue(w)
                    self._distTo[w] = 1 + self._distTo[v]
                    self._edgeTo[w] = v

    # Return the distance within self's graph from from self's vertex
    # to vertex v.
    def distanceTo(self, v):
        return self._distTo[v]

    # Return True if self's graph has a path to vertex v, and False
    # otherwise.
    def hasPathTo(self, v):
        return v in self._distTo

    # Return the path in self's graph from self's vertex to vertex v.
    def pathTo(self, v):
        path = []
        while v is not None:
            path += [v]
            v = self._edgeTo[v]
        return reversed(path)
