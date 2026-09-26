import random
from collections import deque
from typing import List, Optional, Tuple


class MazeGenerator:
    """Generate and solve a maze.

    The maze uses four wall bits per cell:
        bit 0: North
        bit 1: East
        bit 2: South
        bit 3: West
    """

    NORTH = 1
    EAST = 2
    SOUTH = 4
    WEST = 8

    DIRECTIONS = {
        NORTH: (-1, 0),
        EAST: (0, 1),
        SOUTH: (1, 0),
        WEST: (0, -1),
    }

    OPPOSITE = {
        NORTH: SOUTH,
        EAST: WEST,
        SOUTH: NORTH,
        WEST: EAST,
    }

    def __init__(
        self,
        width: int,
        height: int,
        entry: Tuple[int, int],
        exit: Tuple[int, int],
        seed: Optional[int] = None,
        perfect: bool = True,
    ) -> None:
        """Initialize a maze generator.

        Args:
            width: Number of columns.
            height: Number of rows.
            entry: Entry cell as (x, y).
            exit: Exit cell as (x, y).
            seed: Optional random seed.
            perfect: Generate a perfect maze if True.
        """
        self.width = width
        self.height = height
        self.entry = entry
        self.exit = exit
        self.perfect = perfect

        self.random = random.Random(seed)

        self.grid: List[List[int]] = [
            [
                self.NORTH | self.EAST | self.SOUTH | self.WEST
                for _ in range(width)
            ]
            for _ in range(height)
        ]

    def _inside(self, x: int, y: int) -> bool:
        """Return True if a coordinate is inside the maze."""
        return 0 <= x < self.width and 0 <= y < self.height

    def _remove_wall(
        self,
        x: int,
        y: int,
        direction: int,
    ) -> None:
        """Remove a wall between a cell and its neighbour."""
        dx, dy = self.DIRECTIONS[direction]
        nx = x + dy
        ny = y + dx

        if not self._inside(nx, ny):
            return

        self.grid[y][x] &= ~direction
        self.grid[ny][nx] &= ~self.OPPOSITE[direction]

    def _neighbours(
        self,
        x: int,
        y: int,
    ) -> List[Tuple[int, int, int]]:
        """Return unvisited neighbour candidates."""
        result: List[Tuple[int, int, int]] = []

        for direction, (dy, dx) in self.DIRECTIONS.items():
            nx = x + dx
            ny = y + dy

            if self._inside(nx, ny):
                result.append((nx, ny, direction))

        return result

    def _generate_perfect(self) -> None:
        """Generate a perfect maze using randomized DFS."""
        visited = [
            [False for _ in range(self.width)]
            for _ in range(self.height)
        ]

        start_x, start_y = self.entry
        visited[start_y][start_x] = True

        stack: List[Tuple[int, int]] = [(start_x, start_y)]

        while stack:
            x, y = stack[-1]

            neighbours = [
                (nx, ny, direction)
                for nx, ny, direction in self._neighbours(x, y)
                if not visited[ny][nx]
            ]

            if not neighbours:
                stack.pop()
                continue

            nx, ny, direction = self.random.choice(neighbours)

            self._remove_wall(x, y, direction)
            visited[ny][nx] = True
            stack.append((nx, ny))

    def _generate_open(self) -> None:
        """Generate a connected maze with additional loops."""
        self._generate_perfect()

        # Remove additional walls to create loops.
        candidates: List[Tuple[int, int, int]] = []

        for y in range(self.height):
            for x in range(self.width):
                if x + 1 < self.width:
                    candidates.append((x, y, self.EAST))

                if y + 1 < self.height:
                    candidates.append((x, y, self.SOUTH))

        self.random.shuffle(candidates)

        extra_walls = max(1, (self.width * self.height) // 8)

        removed = 0

        for x, y, direction in candidates:
            if removed >= extra_walls:
                break

            if self.grid[y][x] & direction:
                self._remove_wall(x, y, direction)
                removed += 1

    def generate(self) -> List[List[int]]:
        """Generate and return the maze structure."""
        if self.width < 2 or self.height < 2:
            raise ValueError("Maze must be at least 2x2.")

        if self.entry == self.exit:
            raise ValueError("Entry and exit must be different.")

        if not self._inside(*self.entry):
            raise ValueError("Entry is outside the maze.")

        if not self._inside(*self.exit):
            raise ValueError("Exit is outside the maze.")

        if self.perfect:
            self._generate_perfect()
        else:
            self._generate_open()

        return self.grid

    def solve(self) -> str:
        """Return the shortest path from entry to exit."""
        start = self.entry
        target = self.exit

        queue = deque([start])
        previous: dict[
            Tuple[int, int],
            Tuple[Tuple[int, int], str],
        ] = {}

        visited = {start}

        direction_data = [
            (self.NORTH, 0, -1, "N"),
            (self.EAST, 1, 0, "E"),
            (self.SOUTH, 0, 1, "S"),
            (self.WEST, -1, 0, "W"),
        ]

        while queue:
            x, y = queue.popleft()

            if (x, y) == target:
                break

            for wall, dx, dy, letter in direction_data:
                if self.grid[y][x] & wall:
                    continue

                nx = x + dx
                ny = y + dy

                if not self._inside(nx, ny):
                    continue

                neighbour = (nx, ny)

                if neighbour in visited:
                    continue

                visited.add(neighbour)
                previous[neighbour] = ((x, y), letter)
                queue.append(neighbour)

        if target not in visited:
            raise ValueError("No path exists between entry and exit.")

        path: List[str] = []
        current = target

        while current != start:
            parent, letter = previous[current]
            path.append(letter)
            current = parent

        path.reverse()

        return "".join(path)

    def get_grid(self) -> List[List[int]]:
        """Return the generated maze structure."""
        return self.grid