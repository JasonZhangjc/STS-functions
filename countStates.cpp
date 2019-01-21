#include <vector> 
#include <string> 
#include <fstream> 
#include <iostream> 
 
using namespace std; 

/* This program is to count the number of states in Supervisory 
 * Control Report generated by the software STSLib. */
 
void SplitString(const std::string& s, std::vector<std::string>& v, 
                 const std::string& c)
{
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}

int main() 
{ 
    ifstream myfile("no_spec.txt"); 
    string temp;             // Store the content of every line.
    string temp_temp;
    int states = 0;
    int statesThisLine = 1;  // Record the number of states of every line.
    int statesTemp = 1;
    string::size_type position;
    
    if (!myfile.is_open()) 
    { 
        cout << "Couldn't open the file!" << endl; 
    } 
    
      // Count from the right place of the file.
    while(getline(myfile,temp)) 
    { 
        if (temp == "Applying the control patterns above, 
            the system under control can reach the supremal state sets:")
		{
			while(getline(myfile,temp)) 
			{ 
				if(temp.size() != 0)
					statesThisLine = 1;
				
				vector<string> v;
				SplitString(temp, v, ",");             
				// Three inputs: original string, resulting string, seperator.
			
				  // Operate on all clauses after the seperation.
				for(vector<string>::size_type i = 0; i != v.size(); ++i)
				{
					while (position != v[i].npos)   // Operate on each clause.
					{
						position = v[i].find("/");  // find a “/”.
					
						if(position != v[i].npos)
						{
							statesTemp += 1;        
							// Update the number of "/" in each clause.
							
							v[i] = v[i].substr(position + 1);	
						}
					}
					statesThisLine *= statesTemp;
					statesTemp = 1;
					position = 0;
				}
				states += statesThisLine;
				statesThisLine = 0;
			} 
		}
	}
	 
    // Count the number of '/', 
    // though it is not precisely the number of states under all circumstances.
    
    cout << "!!!!!!!!!!!!! " << states << " !!!!!!!!!!!!" << endl;
    
    //***************************************************************
    myfile.close(); 
    //outfile.close();
    getchar();
    return 0; 
}  




