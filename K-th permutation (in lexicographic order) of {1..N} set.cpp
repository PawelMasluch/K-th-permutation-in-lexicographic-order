/*


	Copyright (C) Pawel Masluch, 2021. All rights reserved.
	
	
	
	K-th (in lexicographic order) permutation of {1..N} set.
	
	0 <= N <= 10^7
	1 <= K <= MAX_K = 10^18
	
	Complexity:
		 Time: O(N + N_limit * N_limit)
		Space: O(N_limit)
		
	Note. N_limit = min N: N! > MAX_K.
		
*/

#include<bits/stdc++.h>



typedef long long LL;
typedef std::vector <bool> VB;



#define REP(i,a,b) for(LL i=a; i<=b; ++i)



// min N: N! > MAX_K (in this program: MAX_K = 10^18).
const LL N_limit = 20;



// N! for 0 <= N <= N_limit.
LL factorials[N_limit+1] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, (LL)6227020800, (LL)87178291200, (LL)1307674368000, (LL)20922789888000, (LL)355687428096000, (LL)6402373705728000, (LL)121645100408832000, (LL)2432902008176640000 };



/* 
	Finding N!.
 	
	0 <= N <= 20.
 	
	Complexity:
		 Time: O(N)
		Space: O(1)
		
*/
/*
LL factorial(LL N){
	
	LL res = 1; // 0! = 1!
	REP(i,2,N){
		res *= i;
	}
	
	return res;
}
*/



/*
	Finding the k-th (currently available) minimum element of a vector "remaining" containing a subset A of {0..m-1} set 
	(it is possible that A = {0..m-1}). 
	
	Assumption: the solution exists.
	
	Complexity:
		 Time: O(m)
		Space: O(1)
		
*/
LL find_i_th_element(VB &remaining, LL m, LL k, LL offset){
	LL counter = 0;
	
	REP(i,0,m-1){
		if( remaining[i] == true ){
			++counter;
			
			if( counter == k ){
				remaining[i] = false;
				return i + offset; // we add "offset" to find an original value
			}
		}
	}
}



/*
	An auxiliary procedure finding the K-th (in lexicographic order) permutation of {1..N} set.
	
	1 <= N <= 10^7
	1 <= K <= 10^18
	A solution exists (N! >= K).
	
	Complexity:
		 Time: O(N + N_limit * N_limit)
		Space: O(N_limit)
		
	Note. N_limit = min N: N! > MAX_K.
	
*/
void find_k_th_permutation(LL N, LL K){
	
	/* For i=1..N we find the i-th number of a result permutation. */
	
	// Some preffix of the result permutation will be an identity.
	REP(i, 1, N-N_limit){
		printf( "%lld ", i );
	}
	
	LL offset = std::max((LL)1, N-N_limit+1); // the smallest remaining number to print on output
	LL m = N - offset + 1; // number of remaining elements
	VB remaining (m, true); // remaining elements [offset..N] transformed into [0..m-1] range
	
	// We find the rest of a result permutation.
	REP(i, offset, N){
		LL which_element = (K + factorials[N - i] - 1) / factorials[N - i]; // ceil( K / factorials[N - i] )
		printf( "%lld ", find_i_th_element( remaining, m, which_element, offset ) );
		K -= ( which_element - 1 ) * factorials[N - i];
	}
	printf( "\n" );
}



/* 
	K-th (in lexicographic order) permutation of {1..N} set.
	
	0 <= N <= 10^7
	1 <= K <= 10^18
	
	Complexity:
		Time: O(N + N_limit * N_limit)
		Space: O(N_limit)
		
	Note. N_limit = min N: N! > MAX_K.
	
	Curiosity. We can achieve a better time complexity O(  N + N_limit * log(N_limit)  ) using a range tree 
	(this tree should enable adding a number to a set, deleting a number from a set and searching the k-th minimum in set of numbers).
*/
void k_th_permutation(LL N, LL K){
	
	// Special case: empty permutation.
	if( N == 0 ){
		if( K == 1 ){
			printf( "Empty permutation\n" );
		}
		else{ // K > 1
			printf( "No solution\n" );
		}
		
		return;
	}
	
	
	// ------------------------------------------------
	
	
	if( N >= N_limit ){ // For N >= N_limit we have N! > MAX_K. Thus, a solution always exists (because a number of all permutations of {1..N} set is N!).
		find_k_th_permutation( N, K );	
	}
	else{ // 1 <= N < N_limit
		
		if( factorials[N] < K ){ // if number of all permutations of {1..N} set is smaller than K
			printf( "No solution\n" );
			return;
		}
		
		find_k_th_permutation( N, K );
	}
}



int main(){
	
	LL N, K;
	
	
	// ----------------------
	
	
	printf( "We find the K-th permutation of {1..N} set.\n\nData input\nEnter a length of permutation:\nN = " );
	scanf( "%lld", &N );
	
	printf( "\nEnter a number of found permutation:\nK = " );
	scanf( "%lld", &K );
	
	
	// ----------------------
	
	
	printf( "\n\nThe result:\n" );
	k_th_permutation(N, K);
	
	
	// ----------------------
	
	
	return 0;
}
