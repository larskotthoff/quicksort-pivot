#!/usr/bin/env ruby

numitems = ARGV[0].to_i

# all same
puts numitems.times.collect { 1 }.join(",")

# sorted
puts (1..numitems).to_a.join(",")

# reverse sorted
puts (1..numitems).to_a.reverse.join(",")

# random permutation, no repeated elements
1000.times {
    puts (1..numitems).to_a.sort { rand() - 0.5 }.join(",")
}

# random permutation, repeated elements
1000.times {
    puts (1..Math.sqrt(numitems)).collect { (1..Math.sqrt(numitems)).to_a.sample(numitems) }.flatten.join(",")
}
