#
# from mrubyc support_tools/benchmarks
#

def merge(a, b)
  result = []
  while !a.empty? && !b.empty?
    if a[0] <= b[0]
      result << a.shift
    else
      result << b.shift
    end
  end
  result += a += b
  return result
end

def merge_sort(m)
  if m.length <= 1
    return m
  end
  left, right = [], []
  m.each_with_index do |x, i|
    if i < m.length / 2
      left << x
    else
      right << x
    end
  end
  left = merge_sort(left)
  right = merge_sort(right)
  return merge(left, right)
end

x = 5
ary = []
200.times do
  ary << x
  x = (x * 73) % 887
end

serial_init

loop do
  serial_write('@'.ord)
  1000.times do
    merge_sort(ary)
  end
end

