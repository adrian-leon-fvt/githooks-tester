"""HTTP server: serves the web UI and proxies moves to the C++ engine."""

import json
import re
import subprocess
from http.server import HTTPServer, SimpleHTTPRequestHandler
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ENGINE = ROOT / "build" / "ttt_engine"
WEB = ROOT / "web"


def valid_board(board: object) -> bool:
    """Trust boundary: well-formed and X moved exactly once more than O."""
    return (
        isinstance(board, str)
        and re.fullmatch(r"[XO.]{9}", board) is not None
        and board.count("X") == board.count("O") + 1
    )


def engine_move(board: str) -> dict:
    """Ask the engine for O's reply. Returns {"board": str, "winner": str}."""
    out = subprocess.run(
        [str(ENGINE), board], capture_output=True, text=True, check=True, timeout=5
    )
    return json.loads(out.stdout)


class Handler(SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(WEB), **kwargs)

    def do_POST(self):
        if self.path != "/api/move":
            self.send_error(404)
            return
        try:
            length = min(int(self.headers.get("Content-Length", 0)), 1024)
            board = json.loads(self.rfile.read(length)).get("board")
        except (ValueError, AttributeError):
            board = None
        if not valid_board(board):
            self.send_error(400, "invalid board")
            return
        body = json.dumps(engine_move(board)).encode()
        self.send_response(200)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)


if __name__ == "__main__":
    print("http://localhost:8000")
    HTTPServer(("127.0.0.1", 8000), Handler).serve_forever()
