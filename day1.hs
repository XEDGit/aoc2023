import Data.Char ( isDigit )
import Data.List (elemIndex)
import Data.Maybe (fromJust)

-- Part 1

sumLine :: String -> Int
sumLine []   = error "empty list?"
sumLine line = read [head digits, last digits]
  where digits = filter isDigit line

-- Part 2

stringDigits:: [String]
stringDigits = ["zero",
                "one",
                "two",
                "three",
                "four",
                "five",
                "six",
                "seven",
                "eight",
                "nine"]

translateDigit :: String -> [String] -> (Int, String)
translateDigit line [] = (1, [head line])
translateDigit line (x:xs) | compLine == x = (cmpLen, show(fromJust . elemIndex x $ stringDigits))
                           | otherwise     = translateDigit line xs
  where cmpLen   = length x :: Int
        compLine = take cmpLen line :: String

translateLine :: String -> String
translateLine [] = []
translateLine line = translation ++ translateLine (drop len line)
    where (len, translation) = translateDigit line stringDigits :: (Int, String)

main :: IO()
main = do
  contents <- readFile "input"
  putStr "Part 1:"
  print . sum . map sumLine $ lines contents
  putStr "Part 2:"
  (print . sum) (map (sumLine . translateLine) (lines contents))
