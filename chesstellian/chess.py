class ChessPeice:
  PEICE_NAMES = [
    'pawn',
    'knight',
    'bishop',
    'rook',
    'queen',
    'king',
  ]
  
  def __init__(self, peice_name):
    assert peice_name in ChessPeice.PEICE_NAMES
    self._peice_name = peice_name

  def get_peice_name(self):
    return _peice_name

  def __equal__(self, other):
    return self._peice_name == other._peice_name

class ChessBoard:
  def __init__(self, board = None):
    if board:
      assert len(board) == 8
      for rank in board:
        assert len(rank) == 8
      
      self._board = board

    else:
      self._board = [[None for j in range(8)] for i in range(8)]

  def set_square(self, rank, file, peice):
    self._board[rank][file] = peice

  def get_square(self, rank, file):
    return self._board[rank][file]

  def iter_positions_of_all(self, peice):
    for ri, rank in enumerate(self._board):
      for fi, p in enumerate(rank):
        if p == peice:
          yield ri, fi

  def move(self, old_rank, old_file, new_rank, new_file):
    peice = self.get_square(old_rank, old_file)
    assert peice is not None
    assert peice.can_move(new_rank - old_rank, new_file - old_file)
    self.set_square(old_rank, old_file, None)
    self.set_square(new_rank, new_file, peice)
