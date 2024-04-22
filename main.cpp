#include <cmath>
#include <iostream>
#include "clusters.h"
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

string datafile1 = "../Mall_Customers.csv";
string datafile2 = "../marketing_campaign_processed.csv";

string pointfile1 = "../points1.txt";
string pointfile2 = "../points2.txt";

string clustersfile1 = "../clusters1.txt";
string siluettesfile1 = "../siluettes1.txt";

string clustersfile2 = "../clusters2.txt";
string siluettesfile2 = "../siluettes2.txt";

double EPS = 1e-6;

void normalize_column(int ind, vector<point>& points)
{

  return ;
}


void readpoints(ifstream& in, vector<point>& points)
{

  return ;
}

void write_points(string outfilename, vector<point>& points)
{

}


void write_clusters(string outfilename, vector<point>& points)
{

}

void write_siluettes(string outfilename, vector<cluster>& clusters)
{

}

void test(string input, string pointout, string clustout, string siluetteout)
{

  readpoints(in, points);
  //...
  write_points(pointout, points);
  
  clusteringPAM(points);
  write_clusters(clustout, points);
  //...
  interpreting(points, clusters);
  write_siluettes(siluetteout, clusters);
  
  return;
}



void matrix_processing(string filename)
{
  ifstream in(filename);
  ofstream out(filename.substr(0, filename.size()-4) + "_processed.csv");

  string s;
  getline(in, s);
  out << s << endl;
  vector<vector<string> > M;

  for(;getline(in, s) ;)
  {
    stringstream ss(s);
    string x;
    for(; ss >> x;)
    {
      if (x == "Graduation")
      {
        out << "2 ";
      }
      else if (x == "2n")
      {
        ss >> x;
        out << "1 ";
      }
      else if (x == "Basic")
      {
        out << "0 ";
      }
      else if (x == "Master")
      {
        out << "3 ";
      }
      else if (x == "PhD")
      {
        out << "4 ";
      }
      else if (x == "Together")
      {
        out << "3 ";
      }
      else if (x == "Single")
      {
        out << "0 ";
      }
      else if (x == "Alone")
      {
        out << "0 ";
      }
      else if (x == "Absurd" or x == "YOLO")
      {
        out << "5 ";
      }
      else if (x == "Married")
      {
        out << "4 ";
      }
      else if (x == "Divorced")
      {
        out << "1 ";
      }
      else if (x == "Widow")
      {
        out << "2 ";
      }
      else if (x.size() == 10 && x[2] == '-')
      {
        //cout << x << endl;
        int days = 10*(x[0] - '0') + (x[1] - '0') + 30*( 10*(x[3] - '0') + (x[4] - '0') ) + 365*( (x[6]-'0')*1000 + (x[7] - '0')*100 + (x[8] - '0')*10 + (x[9]-'0'));
        out << days << " ";
      }
      else
      {
        out << x << " ";
      }
    }
    out << endl;
  }
  
  out.close();
  in.close();
}

int main()
{
  //matrix_processing("marketing_campaign.csv");
  //test(datafile1, pointfile1, clustersfile1, siluettesfile1);
  test(datafile2, pointfile2, clustersfile2, siluettesfile2);
 
  return 0;
}
