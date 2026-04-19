# Snake — Arcade Game

A fully-featured, single-file Snake game built with vanilla JavaScript and HTML5 Canvas. No frameworks, no dependencies — just pure browser tech with a polished arcade aesthetic.

---

## Features

**Gameplay**
- Classic Snake mechanics on a 20×20 grid
- 3 lives per game — lose a life on crash or timeout, not the whole run
- 60-second countdown timer per life with a +5s bonus for each fruit eaten
- Score tracking: +10 points per fruit, with a persistent high score for the session

**Visuals**
- Retro arcade UI using Press Start 2P and Orbitron fonts
- Smooth gradient snake body (cyan head → purple tail) with glowing eyes
- Neon-glow fruit with shine highlight
- Animated timer bar that changes colour as time runs low (blue → amber → red)
- Blinking warning animation when under 10 seconds

**UX & Navigation**
- Main menu with player name entry and speed selection (Slow / Normal / Fast)
- In-game HUD: live score, high score, timer, and lives indicator (dot-style)
- Pause overlay on life-loss with contextual messages (CRASHED! / TIME UP! / GAME OVER)
- Session leaderboard with medal rankings for top 3

**Controls**
- Keyboard: Arrow Keys or WASD
- Mobile: on-screen D-pad (auto-shown on small screens)
- 180° reversal prevention built in

---

## Getting Started

No build step required. Just open the file in a browser.

```bash
git clone https://github.com/your-username/snake-game.git
cd snake-game
open index.html
```

Or drag `index.html` directly into any modern browser.

---

## Project Structure

```
snake-game/
└── index.html   ← entire game: HTML, CSS, and JS in one file
```

---

## Tech Stack

| Layer    | Tech                          |
|----------|-------------------------------|
| Rendering | HTML5 Canvas API             |
| Logic    | Vanilla JavaScript (ES6+)     |
| Styling  | CSS3 (animations, grid, flex) |
| Fonts    | Google Fonts (Press Start 2P, Orbitron) |

---

## Customisation

Key constants at the top of the script make it easy to tweak:

```js
const CELL       = 18;   // pixel size of each grid cell
const COLS       = 20;   // grid columns
const ROWS       = 20;   // grid rows
const MAX_LIVES  = 3;    // lives per game
const ROUND_TIME = 60;   // seconds per life
const TIME_BONUS = 5;    // seconds added per fruit eaten
```

---

## License

MIT — free to use, modify, and distribute.
