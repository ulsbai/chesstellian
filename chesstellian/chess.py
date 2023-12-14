class ChessPeice:
  peice_type_ids = {
    'pawn': 0,
    'knight': 1,
    'bishop': 2,
    'rook': 3,
    'queen': 4,
    'king': 5
  }
  
  def __init__(self, peice_type):
    self.peice_type_id = ChessPeice.peice_type_ids[peice_type]

class ChessBoard:
  def __init__(
