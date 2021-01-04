#include <vector>
#include <iostream>
#include <string>
#include <algorithm>   
#include <limits.h>
#define V 50
using namespace std;

class Vertex;
class Edge {
	public:
		Edge(Vertex *org, Vertex *end, int wt) {
			origin=org;
			destination=end;
			weight=wt;
		}
		Vertex* getOrigin() {return origin;}
		Vertex* getDestination() {return destination;}
		int getWeight() {return weight;}

	private:
		Vertex * origin;
		Vertex* destination;
		int weight;
};

class Vertex {
	public:
		Vertex(int id) {
			name=id;
		}
		void addEdge(Vertex *v, int wt) {
			Edge newEdge(this, v, wt);
			edges.push_back(newEdge);
		}
		int getName() {return name;}
		vector<Edge> getEdges() {return edges;}
	
	private:
		int name;
		vector<Edge> edges;
};

class Graphs_P3 {
private:
	vector<Vertex*> vertices;

public:
	void insertVertex(int vertex); //inserts new vertex in graph
	void insertEdge(int from, int to, int weight);  //inserts new edge in graph
	bool isEdge(int from, int to);  //returns true if there is an edge between the vertices from and to
	int getWeight(int from, int to);  //returns the weight of the edge between the vertices from and to
	vector<int> getAdjacent(int vertex);  //return a vector of integers representing vertices adjacent to vertex
	void printDijkstra(int source);  //prints result of running Dijkstra's algorithm with source vertex
	void printGraph(); //prints graph in a format sorted by ascending vertex and edge list
};


void Graphs_P3::insertVertex(int vertex) {
	Vertex *v = new Vertex(vertex);
	vector<Vertex*>::iterator iter;
	for (iter=vertices.begin(); iter!=vertices.end(); iter++) {
		Vertex *start=*iter;
		if (start->getName()==vertex) {
			return;
		}
	}
	vertices.push_back(v);
}

void Graphs_P3::insertEdge(int from, int to, int weight) {
	vector<Vertex*>::iterator iter;
	Vertex *start;
	Vertex *end;

	for (iter=vertices.begin(); iter!=vertices.end(); iter++) {
		Vertex *v=*iter;
		if (v->getName()==from) {
			start=v;
		}
		if (v->getName()==to) {
			end=v;
		}
	}

	if (start->getName()==0) {
		insertVertex(to);
	}
	if (end->getName()==0) {
		insertVertex(from);
	}

	start->addEdge(end, weight);
}

int Graphs_P3::getWeight(int from, int to) {
	vector<Vertex*>::iterator iter;
	Vertex *start;
	Vertex *end;

	for (iter=vertices.begin(); iter!=vertices.end(); iter++) {
		Vertex *v=*iter;
		if (v->getName()==from) {
			start=v;
		}
		if (v->getName()==to) {
			end=v;
		}
	}

	if (start->getName()!=0 && end->getName()!=0) {
		vector<Edge> edges=start->getEdges();
		vector<Edge>::iterator iter;
		for (iter=edges.begin(); iter!=edges.end(); iter++) {
			Edge edge=*iter;
			start=edge.getOrigin();
			end=edge.getDestination();
			if (start->getName()==from && end->getName()==to) {
				return edge.getWeight();
			}
		}
	}
	return 0;
}

bool Graphs_P3::isEdge(int from, int to) {
	vector<Vertex*>::iterator iter;
	Vertex *start;
	Vertex *end;
	bool originFound=false;

	for (iter=vertices.begin(); iter!=vertices.end(); iter++) {
		start=*iter;
		if (start->getName()==from) {
			originFound=true;
			break;
		}
	}

	if (!originFound)
		return false;
	vector<Edge> edges=start->getEdges();
	vector<Edge>::iterator eIter;
	for (eIter=edges.begin(); eIter!=edges.end(); eIter++) {
		Edge edge=*eIter;
		end=edge.getDestination();
		if (end->getName()==to)
			return true;
	}
	return false;
}

vector<int> Graphs_P3::getAdjacent(int vertex) {
	vector<Vertex*>::iterator iter;
	Vertex *start;
	Vertex *end;
	vector<int> adj;

	for (iter=vertices.begin(); iter!=vertices.end(); iter++) {
		start=*iter;
		if (start->getName()==vertex) 
			break;
	}
	
	vector<Edge> edges=start->getEdges();
	vector<Edge>::iterator eIter;
	for (eIter=edges.begin(); eIter!=edges.end(); eIter++) {
		Edge edge=*eIter;
		end=edge.getDestination();
		adj.push_back(end->getName());
	}

	return adj;
}

int minDistance(int dist[], bool sptSt[]) {
	int min=INT_MAX, min_index;

	for (int v=0; v<V; v++)
		if (sptSt[v]==false && dist[v]<=min)
			min=dist[v], min_index=v;

	return min_index;
}

void Graphs_P3::printDijkstra(int source) {
	int dist[V];    
	bool sptSet[V]; 
	string path[V];	

	for (int i=0; i<V; i++)
		dist[i]=INT_MAX, sptSet[i]=false, path[i]="";

	dist[source]=0;
	for (int count=0; count<V-1; count++) {
		int u=minDistance(dist, sptSet);
		sptSet[u]=true;
		for (int v=0; v<V; v++) {
			if (isEdge(u, v)) {
				int wt=0;
				wt=this->getWeight(u, v);
				if (!sptSet[v] && wt && dist[u]!=INT_MAX && dist[u]+wt<dist[v]) {
					dist[v]=dist[u]+wt;
					if (dist[u]==0) {
						path[v]=to_string(u)+"-"+to_string(v);
					}
					else {
						path[v]=path[u]+"-"+to_string(v);
					}
				}
			}
		}
	}

	bool endlput=true;
	cout<<"V D P"<<endl;
	for (int i=0; i<V; i++) {
		if (dist[i]!=0 && dist[i]!=INT_MAX) {
			if (!endlput) {
				cout<<endl;
				endlput=true;
			}
			cout<<i<<" "<<dist[i]<<" "<<path[i];
			endlput=false;
		}
	}
}

void Graphs_P3::printGraph() {
	vector<int> vec;
	Vertex* v;
	Vertex *start;

	for (int i=0; i<vertices.size(); i++) {
		v=vertices[i];
		vec.push_back(v->getName());
	}

	sort(vec.begin(), vec.end());
	vector<int>::iterator ptr;
	vector<Vertex*>::iterator iter;
	vector<int>::iterator eIter;
	bool space=false;

	for (ptr=vec.begin(); ptr<vec.end(); ptr++) {
		for (iter=vertices.begin(); iter!=vertices.end();) {
			start=*iter;
			space=false;
			if (start->getName()==*ptr) {
				cout<<*ptr;
				iter++;
				if (iter!=vertices.end()) {
					cout<<" ";
					space=true;
				}
				vector<int> e=getAdjacent(start->getName());
				sort(e.begin(), e.end());
				for (eIter=e.begin(); eIter!=e.end();) {
					if (!space)
						cout<<" ";
					cout<<*eIter;
					eIter++;
					if (eIter!=e.end())
						cout<<" ";
				}
				cout<<endl;
			}
			else
				iter++;
		}
	}
}

int main()
{
	//DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK
	int noOfLines, operation, vertex, to, fro, weight, source, j;
	vector<int> arr;
	int arrSize;
	Graphs_P3 g;
	cin >> noOfLines;
	for (int i = 0; i<noOfLines; i++)
	{
		cin >> operation;
		switch (operation)
		{
		case 1:
			cin >> vertex;
			g.insertVertex(vertex);
			break;
		case 2:
			cin >> fro;
			cin >> to;
			cin >> weight;
			g.insertEdge(fro, to, weight);
			break;
		case 3:
			cin >> fro;
			cin >> to;
			cout << g.isEdge(fro, to) << "\n";
			break;
		case 4:
			cin >> fro;
			cin >> to;
			cout << g.getWeight(fro, to) << "\n";
			break;
		case 5:
			cin >> vertex;
			arr = g.getAdjacent(vertex);
			arrSize = arr.size();
			j = 0;
			while (j<arrSize)
			{
				cout << arr[j] << " ";
				j++;
			}
			cout << "\n";
			break;
		case 6:
			cin >> source;
			g.printDijkstra(source);
			cout << "\n";
			break;
		case 7:
			g.printGraph();
			cout << "\n";
			break;
		}
	}
}