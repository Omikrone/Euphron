# Change Log


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