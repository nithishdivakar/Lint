#ifndef __SHORTS__
#define __SHORTS__

#include <vector>
#include <algorithm>
#include<cstdint>

typedef std::vector< int > vi;
typedef std::vector< vi > vvi;
#define sz(a) int((a).size())
#define ALL(c) (c).begin(),(c).end()
#define TRAV(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define RTRAV(c,i) for(typeof((c).rbegin()) i = (c).rbegin(); i != (c).rend(); i++)
#define present(c,x) ((c).find(x) != (c).end()).
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define UNTIL(x) while(!(x))


#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define PRINT(a) printf("%d ",(a))
#define PRINTS(a) printf("%s ",(a))
#endif
