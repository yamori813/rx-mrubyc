#
# mrbc -E -Bsample_serial_echo_server sample_serial_echo_server.rb
#

character = 0

serial_init

loop do
  character = serial_read
  serial_write(character)
end
