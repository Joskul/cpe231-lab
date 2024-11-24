#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

int firstTrueIndex(bool arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i]) {
            return i;
        }
    }
    return -1; // No true value in array
}

int indexOf(int arr[], int size, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) {
            return i;
        }
    }
    return -1;
}

void stableMarriage(int n, int mPref[][MAX], int wPref[][MAX], int mPartner[]) {
    bool mFree[MAX];
    memset(mFree, true, sizeof(mFree)); // Initialize all men as free

    for (int i = 0; i < n; i++) {
        mPartner[i] = -1; // Initialize men's partners as none
    }

    for (int mIndex = firstTrueIndex(mFree, n); mIndex != -1; mIndex = firstTrueIndex(mFree, n)) {
        for (int mChoice = 0; mChoice < n && mFree[mIndex]; mChoice++) {
            int wOfChoice = mPref[mIndex][mChoice];
            int wPartner = indexOf(mPartner, n, wOfChoice);

            if (wPartner == -1) { // Woman of preference is free
                mPartner[mIndex] = wOfChoice; // Proposal accepted
                mFree[mIndex] = false;
            } else { // Woman of preference is already engaged
                if (indexOf(wPref[wOfChoice], n, wPartner) > indexOf(wPref[wOfChoice], n, mIndex)) {
                    // If she prefers mIndex over her current partner
                    mPartner[mIndex] = wOfChoice; // Proposal accepted
                    mFree[mIndex] = false;

                    // Break the engagement
                    mPartner[wPartner] = -1;
                    mFree[wPartner] = true;
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int internRank[MAX][MAX]; // Intern ranking each company gave
    int companyRank[MAX][MAX]; // Company ranking each intern gave

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &internRank[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &companyRank[i][j]);
        }
    }

    int mPartner[MAX]; // Result array for men's partners
    stableMarriage(n, companyRank, internRank, mPartner);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", i, mPartner[i]);
    }

    return 0;
}
