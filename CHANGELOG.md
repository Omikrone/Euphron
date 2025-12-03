# Change Log

## [0.2.0] - 2025-12-03

### Added

- Added functionality to either run the UCI engine or use the API wrapper based on command-line arguments.
- Implemented WebSocket communication for the API wrapper to interact with the Chessgame project.
- Implemented iterative deepening in the search algorithm to handle time constraints better.
- Added basic UCI command options like "movetime".
- Implemented UCI thread management for handling multiple commands concurrently.
- Implemented search flag to stop the search when required.
- Added possibility for the engine to play as either white or black based on UCI commands.

### Fixed
- Fixed handling of no best move found during search, ensuring the engine returns a valid move.


## [0.1.2] - 2025-10-25

### Added

- Added compatibility with Chessboard library version 1.3.0.

### Fixed

- Fixed the engine not switching turns correctly during search, leading to incorrect evaluations and crashes.


## [0.1.1] - 2025-10-25

### Fixed

- Fixed the case when the engine crashes if no best moves were found.


## [0.1.0] - 2025-10-19

### Added

- Basic evaluation function considering only material balance.
- Minimax search algorithm for move selection.

### Removed

- Generation of random legal moves.

### Fixed

- Avoid engine crash when no legal moves are available.
- Avoid engine crash when game is finished.


## [0.0.0] - 2025-10-05

### Added

- Initial release with UCI protocol implementation.
- API Wrapper for communication with the Chessgame project.
- Generation of random legal moves.