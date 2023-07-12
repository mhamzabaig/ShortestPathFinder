#include<iostream>
#include<vector>
#include<math.h>
#include<list>
#include<conio.h>
using namespace std;

//--------------------Implementing A STAR ALGORITHM For Finding Shortest Path---------------------

const int scr_rows = 20;
const int scr_cols = 20;

// structure of a Node in the graph
struct node
{
    string ch; // ch determines either the node is an obstacle ( I ) or a free space ( . ) to move or the shortest path node ( P ) 
    bool is_visited = false;
    int x_cord;
    int y_cord;
    int local_score;
    int global_score;
    node* parent;
    vector<node*> Neighbours;
};

node* screen = new node[scr_rows*scr_cols];

void creating_Grid()
{
    // Initializing nodes with thier responding coordinates 
    for(int x = 0; x<scr_rows;x++)
    {
        for(int y=0; y<scr_cols; y++)
        {
            screen[x*scr_rows + y].x_cord = x;
            screen[x*scr_rows + y].y_cord = y;
            screen[x*scr_rows + y].ch = "  -  ";
            screen[x*scr_rows + y].is_visited = false;
            screen[x*scr_rows + y].parent = NULL;
        } 
    }

    // Creating connections with adjacent neighbours
    for(int x = 0; x<scr_rows;x++)
    {
        for(int y=0; y<scr_cols; y++)
        {
            if(y>0)                 // upper parent/adjacent
				screen[y*scr_rows + x].Neighbours.push_back(&screen[(y - 1) * scr_rows + (x + 0)]);

			if(y<scr_cols-1)        // lower parent/adjacent
				screen[y*scr_rows + x].Neighbours.push_back(&screen[(y + 1) * scr_rows + (x + 0)]);

			if (x>0)                // left parent/adjacent
				screen[y*scr_rows + x].Neighbours.push_back(&screen[(y + 0) * scr_rows + (x - 1)]);

			if(x<scr_rows-1)        // right parent/adjacent
				screen[y*scr_rows + x].Neighbours.push_back(&screen[(y + 0) * scr_rows + (x + 1)]);

            if(y>0 && x>0)                 // Downward Left DIAGNOL Parent/Adjacent
				screen[y*scr_rows + x].Neighbours.push_back(&screen[(y - 1) * scr_rows + (x - 1)]);

			if(y>0 && x<scr_rows-1)        // Downward Right Diagnol Parent/Adjacent
				screen[y*scr_rows + x].Neighbours.push_back(&screen[(y - 1) * scr_rows + (x + 1)]);

			if (y<scr_cols-1 && x>0)                // Upper Left Diagnol Parent/Adjacent
				screen[y*scr_rows + x].Neighbours.push_back(&screen[(y + 1) * scr_rows + (x - 1)]);

			if(y<scr_cols-1 && x<scr_rows-1)        // UPPEr Right Diagnol Parent/Adjacent
				screen[y*scr_rows + x].Neighbours.push_back(&screen[(y + 1) * scr_rows + (x + 1)]);

                    
        } 
    }

}


float distance(node* a, node* b)  // distance formula = sqrt((x2-x1)2 + (y2-y1)2)
{
	return sqrtf((a->x_cord - b->x_cord)*(a->x_cord - b->x_cord) + (a->y_cord - b->y_cord)*(a->y_cord - b->y_cord));
}

float heuristic  (node* a, node* b) // Here this heuristic is just distance of current node to the end node 
{
        return distance(a,b);
}

void shortest_Path(node*source_node, node* dest_node)
{
    // Using Parents to make a shortest path from destination to source going backward direction
    while(dest_node != source_node)
    {
        if(dest_node->ch != "  :) ") // Checking that we are not replacing our destination node with P
        {
            dest_node->ch = "  P  ";
        }
        dest_node = dest_node->parent;
    }
}

bool A_star_Algo() // Making it a bool function so that I can abort anywhere from inside the function if user makes any mistake......
{
    
    // Taking Starting( S ) Ending ( E ) and obstacles ( I ) positions from the user......
    int start, end;
    cout<<"\nEnter Start_Node position : ";cin>>start;
    cout<<"Enter End_Node position : ";cin>>end;
    
    if(start<0 || start>(scr_cols*scr_cols)-1 || end>(scr_cols*scr_cols)-1 || end<0) // Error HANDLING 
    {
        return false; // ABORT As user has given wrong input
    }

    //    Selecting Start and End points...........
    node* start_node = &screen[start];
    start_node->ch = "  :( ";  // :( showing the start node he is sad cause he is trapped....
    node* end_node = &screen[end];
    end_node->ch =   "  :) ";    // :) showing the end node and now he is happy...


    //OBSTACLES PART
    while(true)  // True creates an infinite loop and break statement will terminate the loop
    {
        int obs; // obstacle choice whether user want to enter an obstacle or not. Initially its true
        
        cout<<"\nWant to place 10 obstacles vertically  (1(Y) or 0(N)) ";
        cin>>obs; 

        if(obs == start || obs == end)
        {
            cout<<" Oooops you have selected wrong obstacle position.. PLease Try Again..."<<endl;
            return false;
        }

        if(obs > 1 || obs < 0) // Error HANDLING 
        {
            return false; // ABORT As user has given wrong input
        }

        if(obs == 1)
        {
            int obs_pos; // obstacle coordinates
            cout<<"\nEnter the position of obstacle : ";cin>>obs_pos;

            //screen[obs_pos].ch = " I " ;   // for placing 1 obstacle at a time....
            
            // For five obstacles at a time downward 
             
            for(int i=0; i<200 ; i+=scr_rows)
            {
                if(obs_pos+i < scr_cols*scr_rows)
                {
                    screen[obs_pos+i].ch = "  I  " ;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            break; // if user does not want to place any obstacle further loop will terminate
        }
    }


    // Reseting Navigation...
    for(int x=0; x<scr_rows; x++)
    {
        for(int y=0; y<scr_cols; y++ )
        {
            screen[x*scr_rows + y].local_score = INFINITY;
            screen[x*scr_rows + y].global_score = INFINITY;
            screen[x*scr_rows + y].parent = NULL;

        }
    }

    node *nodeCurrent = start_node;
	start_node->local_score = 0.0f;
	end_node->global_score = heuristic(start_node,end_node);
    
    list<node*> listNotTestedNodes;
    listNotTestedNodes.push_back(start_node);

    while(listNotTestedNodes.empty() == false && nodeCurrent != end_node) // finding shortest path and !lNTN.empty() --> LNTN.empty() == false
	{
        // Sort Untested nodes by global goal, so lowest is first
        listNotTestedNodes.sort([](const node* lhs, const node* rhs)
        { return lhs->global_score < rhs->global_score; } );

        // Front of listNotTestedNodes is potentially the lowest distance node. Our
		// list may also contain nodes that have been visited, so ditch these...

		while(listNotTestedNodes.empty() == false && listNotTestedNodes.front()->is_visited == true)
			{
                listNotTestedNodes.pop_front();
            }

		// ...or abort because there are no valid nodes left to test
		
        if (listNotTestedNodes.empty())  // --> listNotTestedNodes.empty() == true
			break;

		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->is_visited = true; // We only explore a node once

        // Now checking each neighbour of current node
        for(auto neighbour_Node: nodeCurrent->Neighbours)
        {
            // Check if the neighbour is visited or not and its an obstacle or not

            if(neighbour_Node->is_visited == false && neighbour_Node->ch != "  I  ")
            {
                listNotTestedNodes.push_back(neighbour_Node); // adding to list to check further paths
            }

            // Calculating Minimum lower_score to find the best parent neighbour
            

            float min_score = nodeCurrent->local_score + distance(nodeCurrent,neighbour_Node);

            if(min_score < neighbour_Node->local_score)
            {
                neighbour_Node->parent = nodeCurrent;
                neighbour_Node->local_score = min_score;

                // As the neighbour has been updated so the global scope will also be changed to help the algorithhn

                neighbour_Node->global_score = neighbour_Node->global_score + heuristic(neighbour_Node,end_node);
            } 
        }
    }

    shortest_Path(start_node,end_node);

    return true;
}

void display_Path()
{
    cout<<"\n--------------------------------------//////// CITY MAP \\\\\\\\\\\\\\\\---------------------------------------"<<endl<<endl;
    cout<<" ............DSA WAS STUCKED AND SAD :( IN THIS CITY OF STRANGE PEOPLE GUIDING HIM WRONG DIRECTION...... "<<endl<<endl;
    cout<<".............THEN HE FOUND OUT THIS PATH FINDER ............................................................."<<endl<<endl;
    for(int r=0; r<scr_cols; r++)
    {
        for(int c=0; c<scr_rows; c++)
        {
            cout<<screen[r*scr_rows + c].ch;
        }
        cout<<endl;
    }

    cout<<"\n\n NOW HE IS HAPPY :) CAUSE HE HAd REACHED DESTINATION USING PATH FINDER..................................."<<endl<<endl;
}

int main()
{
    cout<<" DO U WANT TO GO SOMEWHERE (Y/N) --->>> ";
    char run_algo = getche();

    while(run_algo == 'y' || run_algo == 'y')
    {
        creating_Grid(); // For creating Screen of City
        
        if(A_star_Algo())   // For finding shortest path
        {
            display_Path();      // For displaying path
        }
        else
        {
            cout<<" There has been a mistake.. Please TrY AGaiN----- "<<endl;
        }
        

        cout<<" HeY THeRe WaNNa GO SOMEWHERE (Y/N) --->>> ";
        run_algo = getche();
    }
    // cout<<" \n Project BY Ibrahim Asif & M Hamza Baig "<<endl;
    // cout<<" Submitted to Shahmin Sharafat "<<endl;
    // cout<<"\n SeE YaAAAAA  :)"<<endl;

}