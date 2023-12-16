import Data.Char

sumLine:: [Char] -> Int
sumLine line = read [head digits, last digits]
  where digits = filter isDigit line

main :: IO()
main = do
  contents <- readFile "input"
  let linesArr = lines contents
  print . sum . map sumLine $ linesArr