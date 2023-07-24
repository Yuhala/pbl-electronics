

from pytapo import Tapo

user = "petersonyuhala@gmail.com" # user you set in Advanced Settings -> Camera Account
password = "" # password you set in Advanced Settings -> Camera Account fb@2k!
host = "" # ip of the camera, example: 192.168.1.52

tapo = Tapo(host, user, password)

print(tapo.getBasicInfo())