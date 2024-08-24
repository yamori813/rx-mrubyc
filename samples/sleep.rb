#
# built in method sleep test
#

def print(val)
  val.to_s.each_char do |n|
    serial_write(n.ord)
  end
end

begin
  serial_init

  loop do
    serial_write(0x2a)
    sleep 1
  end
rescue StandardError => e
  print e
end
