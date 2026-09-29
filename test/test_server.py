"""Server checks: input validation and round-trip through the real engine."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "server"))
import app


class ServerTest(unittest.TestCase):
    def test_valid_board(self):
        self.assertTrue(app.valid_board("X........"))
        self.assertFalse(app.valid_board("........."))  # X must move first
        self.assertFalse(app.valid_board("XX......."))  # turn order
        self.assertFalse(app.valid_board("X;rm -rf/"))
        self.assertFalse(app.valid_board(None))

    def test_engine_blocks(self):
        self.assertEqual(app.engine_move("XX..O....")["board"], "XXO.O....")


if __name__ == "__main__":
    unittest.main()
