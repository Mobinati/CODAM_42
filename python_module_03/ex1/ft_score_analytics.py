#!/usr/bin/env python3

import sys

if __name__ == "__main__":
    print("=== Player Score Analytics ===")
    if len(sys.argv) == 1:
        print(f"No scores provided. Usage: "
              f"python3 {sys.argv[0]} <score1> <score2> ...")

    else:
        scores = []
        if len(sys.argv) > 1:
            for arg in sys.argv[1:]:
                try:
                    scores.append(int(arg))
                except ValueError:
                    print(f"Invalid parameter: '{arg}'")
        if len(scores) == 0:
            print(f"No scores provided. Usage: python3"
                  f" {sys.argv[0]} <score1> <score2> ...")

        else:
            print(f"Scores processed: {scores}")
            print(f"Total players: {len(scores)}")
            print(f"Total score: {sum(scores)}")
            print(f"Average score: {sum(scores)/len(scores)}")
            print(f"High score: {max(scores)}")
            print(f"Low score: {min(scores)}")
            print(f"Score range: {max(scores) - min(scores)}")
