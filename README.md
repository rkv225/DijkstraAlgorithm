\# DijkstraAlgorithm
Visual C++ CLR Forms Application which calculates the shotest path using the popular Dijkstra's Algorithm

## Getting Started
You must have Visual Studio Installed in order to run this Project.
Open up the Repository into the Visual Studio or Double Click the .sln file to fire Visual Studio.

## Running

### Screenshots
<img src="~\Screens\01.png">

### Algorithm
```C++
void calcShortestDist()

		{

			infDist();

			//marking the source node as visited, it's distance to  and adding to the path

			visited[sourceNode] = 1;

			path[pathIndex++] = sourceNode;

			distance[sourceNode] = 0;



			//setting the currNode to sourceNode

			currNode = sourceNode;



			//finding the shortest path to the destination

			for (int i = 0; i < n; i++)

			{

				if (currNode == destNode) // already reached the destination

					break;

				int smallest = INFINITE, smallestIndex;

				int allVisited = 0;

				for (int j = 0; j < n; j++)

				{

					if (visited[j] == 1) //node already visited will be skipped

					{

						allVisited++;

						continue;

					}

					if (j == currNode) //if on the same node then skip

						continue;

					if (adj[currNode,j] != 0) //nodes are adjacent to eachother

					{

						if (distance[j] > (distance[currNode] + adj[currNode, j])) // if shorter distance available then put it

							distance[j] = distance[currNode] + adj[currNode, j];

					}

					if (smallest > distance[j]) // for getting node with smallest distance

					{

						smallest = distance[j];

						smallestIndex = j;

					}

				}



				if (allVisited == n) //if already visited all nodes then stop the operation 

					break;



				path[pathIndex++] = smallestIndex;

				visited[smallestIndex] = 1;

				currNode = smallestIndex;

			}



			//initializing values for route

			index = 0;

			//k = 0;

			i = pathIndex - 1;

			j = pathIndex - 2;



			//finding the shortest route

			setMarkingPen();

			while (i >= 0)

			{

				if (i == 0)

				{

					//route[k++] = path[i];

					break;

				}

				if (adj[path[i], path[j]] == (distance[path[i]] - distance[path[j]]) && adj[path[i], path[j]] != 0) //verifying that the distance equals the path

				{

					//route[k++] = path[i];

					markEdge(path[i], path[j]);

					i = j;

					j--;

				}

				else

				{

					j--;

				}

			}

			resettingPens();

		}
```
    
