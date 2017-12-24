-- Coding Assignment 6.5
myfoldr1 :: (a -> a -> a) -> [a] -> a
myfoldr1 f [] = error "empty list"
myfoldr1 f [x] = x
myfoldr1 f x = f (head x) (myfoldr1 f (tail x))

-- Coding Assignment 6.6
myfoldr :: (a -> b -> b) -> b -> [a] -> b
myfoldr f n [] = n
myfoldr f n ls = f (head ls) (myfoldr f n (tail ls))

-- Coding Assignment 6.7
myfilterA :: [a] -> (a -> Bool) -> [a]
myfilterA ls f = [ch | ch <- ls, (f ch) == True]

myfilterB :: [a] -> (a -> Bool) -> [a]
myfilterB [] f = []
myfilterB ls f
  | f (head ls) == True = [head ls] ++ myfilterB (tail ls) f
  | otherwise = myfilterB (tail ls) f

-- Coding Assignment 6.8
titleMachine :: String -> (String -> String)
titleMachine s1 s2 = s1 ++ " " ++ s2

-- Coding Assignment 6.9
binaryArgFlip :: (a -> b -> c) -> (b -> a -> c)
binaryArgFlip f b a = f a b

-- Coding Assignment 6.11
totalLa :: (Integer -> Integer) -> (Integer -> Integer)
totalLa f = (\n -> foldr1 (+) (map f [0..n]))

totalPa :: (Integer -> Integer) -> (Integer -> Integer)
totalPa f n = foldr1 (+) [f i | i <- [0..n]]

-- Coding Assignment 6.12
curry3 :: ((a, b, c) -> d) -> (a -> b -> c -> d)
curry3 g x y z = g (x, y, z)

uncurry3 :: (a -> b -> c -> d) -> ((a, b, c) -> d)
uncurry3 g (x, y, z) = g x y z
