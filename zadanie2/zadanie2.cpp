#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

pair<float,float> start_point;

float cross(pair<float,float> P0, pair<float,float> A, pair<float,float> B){
    return (A.first - P0.first) * (B.second - P0.second) -
           (A.second - P0.second) * (B.first - P0.first);
}

bool polar_cmp(const pair<float,float>& a, const pair<float,float>& b){
  float c = cross(start_point, a, b);
  if (c == 0){
      float da = (a.first-start_point.first)*(a.first-start_point.first) +
                 (a.second-start_point.second)*(a.second-start_point.second);
      float db = (b.first-start_point.first)*(b.first-start_point.first) +
                 (b.second-start_point.second)*(b.second-start_point.second);
      return da < db;
  }
  return c > 0;
}


vector<pair<float, float>> convex_hull(vector<pair<float, float>> points){
  // Znajdowanie najbardziej wychylonego na dół punktu
  // Jeżeli istnieją dwa takie to szukamy takiego z nich,
  // który jest wychylony najbardziej na lewo
  if (points.size() <= 3){
    return points;
  }
  int start = 0;
  for (int i=0; i<points.size(); i++){
    if (points[i].second < points[start].second || 
        (points[i].second == points[start].second &&
         points[i].first < points[start].first)){
      start = i;
    }
  }
  swap(points[0], points[start]);
  // ustawiamy punkty startowy na ten znaleziony punkt
  start_point = points[0];
  // a następnie sortujemy resztę punktów według kąta względem tego punktu
  sort(points.begin()+1, points.end(), polar_cmp);

  // teraz z tymi danymi możemy stworzyć "stos" z otoczką wypukłą
  vector<pair<float, float>> stack;
  stack.push_back(points[0]);
  stack.push_back(points[1]);
  stack.push_back(points[2]);
  pair<float, float> top, next;

  for (int i=3; i < points.size(); i++){
    while (stack.size() >= 2){
      top = stack.back();
      next = stack[stack.size()-2];
      if (cross(next, top, points[i])>0){
        break;
      }
      stack.pop_back();
    }
    stack.push_back(points[i]);
  }
  return stack;
}

int main (int argc, char *argv[]) {
  ifstream input_file("input.txt");
  if (!input_file){
    cerr << "Nie udało się otworzyć pliku" << endl;
    return 1;
  }
  string line;
  getline(input_file, line);
  int n = stoi(line);
  vector<pair<float, float>> points(n);
  for (int i=0; i<n; i++){
    getline(input_file, line);
    stringstream ss(line);
    float x,y;
    ss >> x >> y;
    points[i] = make_pair(x, y);
  }
  // convex hull
  vector<pair<float, float>> hull = convex_hull(points);
  cout << "Otoczka:" << endl;
  for (int i=0; i<hull.size(); i++){
    cout << hull[i].first << "\t" << hull[i].second << endl;
  }

  return 0;
}
