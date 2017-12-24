module Assignment8 where
  import Data.List

  -- Coding Assignment 8.1 --
  data MyBinaryTree a = NullNode | Node a (MyBinaryTree a) (MyBinaryTree a)
    deriving (Show, Eq)

  -- Coding Assignment 8.2 --
  leftTree :: MyBinaryTree a -> MyBinaryTree a
  leftTree NullNode = NullNode
  leftTree (Node _ l _) = l

  rightTree :: MyBinaryTree a -> MyBinaryTree a
  rightTree NullNode = NullNode
  rightTree (Node _ _ r) = r

  -- Coding Assignment 8.3 --
  treeElem :: Eq a => a -> MyBinaryTree a -> Bool
  treeElem v NullNode = False
  treeElem v (Node nv l r) = (v == nv) ||
                             (treeElem v l) ||
                             (treeElem v r)

  -- Coding Assignment 8.4 --
  treeMax :: Ord o => MyBinaryTree o -> Maybe o
  treeMax NullNode = Nothing
  treeMax (Node v l r) = max (Just v) (max (treeMax l) (treeMax r))

  treeMin :: Ord o => MyBinaryTree o -> Maybe o
  treeMin NullNode = Nothing
  treeMin (Node v l r) = nMin (Just v) (nMin (treeMin l) (treeMin r))
    where nMin x y = if x == Nothing
                        then y
                      else if y == Nothing
                        then x
                      else
                        min x y

  -- Coding Assignment 8.5 --
  reflectTree :: MyBinaryTree a -> MyBinaryTree a
  reflectTree NullNode = NullNode
  reflectTree (Node v l r) = Node v (reflectTree r) (reflectTree l)

  -- Coding Assignment 8.5 --
  collapseTree :: MyBinaryTree a -> [a]
  collapseTree NullNode = []
  collapseTree (Node v l r) = (collapseTree l) ++ [v] ++ (collapseTree r)

  -- Coding Assignment 8.6 --
  isBST :: Ord o => MyBinaryTree o -> Bool
  isBST NullNode = True
  isBST (Node v l r) = isBST l && isBST r &&
                       (treeMax l) < (Just v) &&
                       if (treeMin r) == Nothing
                         then True
                       else (treeMin r) > (Just v)

  -- Coding Assignment 8.7 --
  bstAdd :: Ord o => o -> MyBinaryTree o -> MyBinaryTree o
  bstAdd v NullNode = (Node v NullNode NullNode)
  bstAdd v (Node nv l r) = if v < nv
                             then Node nv (bstAdd v l) r
                           else Node nv l (bstAdd v r)

  -- Coding Assignment 8.8 --

  -- First attempt, not balanced.
  listToBST' :: Ord o => [o] -> MyBinaryTree o
  listToBST' [] = NullNode
  listToBST' (x:[]) = (Node x NullNode NullNode)
  listToBST' ls = (Node (minimum ls) NullNode (listToBST (tail ls)))

  -- support func for listToBST
  sortAndSplit :: Ord o => [o] -> ([o], [o])
  sortAndSplit ls = ((take l sortedls), (drop l sortedls))
    where l = floor ((read (show (length ls)) :: Float) / 2)
          sortedls = sort ls

  -- Second attempt, balanced.
  listToBST :: Ord o => [o] -> MyBinaryTree o
  listToBST [] = NullNode
  listToBST (x:[]) = (Node x NullNode NullNode)
  listToBST ls = (Node (maximum l) (listToBST (init l)) (listToBST u))
    where (l, u) = sortAndSplit ls

  treeToBST :: Ord o => MyBinaryTree o -> MyBinaryTree o
  treeToBST t = listToBST (collapseTree t)

  -- Coding Assignment 8.9 --
  delFromBST :: Ord o => o -> MyBinaryTree o -> MyBinaryTree o
  delFromBST v NullNode = NullNode
  delFromBST v t = if binaryLookup v t
                     then listToBST (delete v (collapseTree t))
                   else t

  -- Coding Assignment 8.10 --
  binaryLookup :: Ord o => o -> MyBinaryTree o -> Bool
  binaryLookup v NullNode = False
  binaryLookup v (Node nv l r) =
    if v == nv
      then True
    else
      if v < nv
        then False || binaryLookup v l
      else False || binaryLookup v r

  -- Coding Assignment 8.11 --
  data FifoQueue a = EmptyQueue | QueueNode a (FifoQueue a)
    deriving (Show, Eq)

  qadd :: a -> FifoQueue a -> FifoQueue a
  qadd v EmptyQueue = (QueueNode v EmptyQueue)
  qadd v (QueueNode nv rq) = QueueNode nv (qadd v rq)

  qpop :: FifoQueue a -> (FifoQueue a, Maybe a)
  qpop EmptyQueue = (EmptyQueue, Nothing)
  qpop (QueueNode v q) = (q, Just v)

  isEmpty :: FifoQueue a -> Bool
  isEmpty EmptyQueue = True
  isEmpty (QueueNode _ _) = False
