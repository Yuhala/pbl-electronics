
import os
import json
import time
import pytest
from pytapo import Tapo


user = "petersonyuhala@gmail.com" # user you set in Advanced Settings -> Camera Account
password = "" # password you set in Advanced Settings -> Camera Account fb@2k!
host = "" # ip of the camera, example: 192.168.1.52

tapo = Tapo(host, user, password)

print(tapo.getBasicInfo())


# Motor movement functions
def test_moveMotorStep():
    tapo = Tapo(host, user, password)
    origPrivacyModeEnabled = tapo.getPrivacyMode()["enabled"] == "on"
    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(False)
    result1 = tapo.moveMotorStep(10)
    time.sleep(5)
    result2 = tapo.moveMotorStep(190)
    time.sleep(5)

    with pytest.raises(Exception) as err:
        tapo.moveMotorStep(360)
    assert "Angle must be in a range 0 <= angle < 360" in str(err.value)
    with pytest.raises(Exception) as err:
        tapo.moveMotorStep(-1)
    assert "Angle must be in a range 0 <= angle < 360" in str(err.value)

    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(True)
    assert result1["error_code"] == 0
    assert result2["error_code"] == 0


def test_moveMotorClockWise():
    tapo = Tapo(host, user, password)
    origPrivacyModeEnabled = tapo.getPrivacyMode()["enabled"] == "on"
    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(False)
    result = tapo.moveMotorClockWise()
    time.sleep(5)

    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(True)
    assert result["error_code"] == 0


def test_moveMotorCounterClockWise():
    tapo = Tapo(host, user, password)
    origPrivacyModeEnabled = tapo.getPrivacyMode()["enabled"] == "on"
    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(False)
    result = tapo.moveMotorCounterClockWise()
    time.sleep(5)

    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(True)
    assert result["error_code"] == 0


def test_moveMotorVertical():
    tapo = Tapo(host, user, password)
    origPrivacyModeEnabled = tapo.getPrivacyMode()["enabled"] == "on"
    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(False)
    result = tapo.moveMotorVertical()
    time.sleep(5)

    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(True)
    assert result["error_code"] == 0


def test_moveMotorHorizontal():
    tapo = Tapo(host, user, password)
    origPrivacyModeEnabled = tapo.getPrivacyMode()["enabled"] == "on"
    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(False)
    result = tapo.moveMotorHorizontal()
    time.sleep(5)

    if origPrivacyModeEnabled:
        tapo.setPrivacyMode(True)
    assert result["error_code"] == 0
