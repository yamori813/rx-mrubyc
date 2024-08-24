#
# serial echo back test script
#

character = 0

serial_init

loop do
  character = serial_read
  serial_write(character)
end
