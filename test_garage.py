#! /usr/bin/env python3
import datetime
import unittest

import pytest

import garage


class TestGarage(unittest.TestCase):
    DELTA = 1e-5

    def test_ex1(self):
        car = garage.Car(year=2018)
        self.assertEqual(car.year, 2018)

        car = garage.Car(name="our test car")
        self.assertEqual(car.name, "our test car")

        car = garage.Car(price=42)
        self.assertEqual(car.price, 42)

        car = garage.Car(max_people=23)
        self.assertEqual(car.max_people, 23)

        car = garage.Car(max_goods=4321)
        self.assertEqual(car.max_goods, 4321)

        car = garage.Car(tank_capacity=4321)
        self.assertEqual(car.tank_capacity, 4321)

        car = garage.Car(gas_consumption=20)
        self.assertEqual(car.gas_consumption, 20)

        car = garage.Car()
        self.assertEqual(car.year, 2020)
        self.assertEqual(car.name, "bagnole")
        self.assertEqual(car.price, 25000)
        self.assertEqual(car.max_people, 5)
        self.assertEqual(car.max_goods, 500)
        self.assertEqual(car.tank_capacity, 42)
        self.assertEqual(car.gas_consumption, .062)
        self.assertEqual(car.odometer, 0)
        self.assertEqual(car.gas_level, 0)

    def test_ex2(self):
        car = garage.Car(year=2000)
        # Uncomment if we reconsider this method as a value.
        # self.assertTrue(isinstance(garage.Car.value, property), msg="value is not defined as a property")
        self.assertAlmostEqual(car.compute_value(), 0, delta=TestGarage.DELTA,
                               msg="Value of an old car should not be below 0")

        car = garage.Car(year=datetime.datetime.now().year, max_people=3)
        # Uncomment if we reconsider this method as a value.
        # self.assertTrue(isinstance(garage.Car.value, property), msg="value is not defined as a property")
        self.assertAlmostEqual(car.compute_value(), 28125, delta=TestGarage.DELTA)
        car.odometer = 500
        self.assertAlmostEqual(car.compute_value(), 28112.5, delta=TestGarage.DELTA)

    def test_ex3(self):
        with self.assertRaises(FileNotFoundError, msg="Should not be able to open a non existing file"):
            (garage.load_cars("not_found.csv"), [])
        self.assertEqual(garage.load_cars("empty.csv"), [])
        car = garage.Car(name="Audi Q3", price=52000, year=2019, max_people=5, max_goods=475, tank_capacity=64,
                         gas_consumption=.079)
        self.assertEqual(garage.load_cars("one.csv"), [car])

    def test_ex4(self):
        service = garage.RentalService([])
        self.assertEqual([], service.cars)

        cars = [garage.Car(name="super voiture", year=2017, max_people=23, max_goods=2)]
        service = garage.RentalService(cars)
        self.assertEqual(cars, service.cars)

    def test_ex5(self):
        car = garage.Car(name="super voiture", year=datetime.datetime.now().year - 3, max_people=5, max_goods=500)
        cars = [car]
        service = garage.RentalService(cars)
        self.assertEqual([(car, 525.151388888889)], service.search(2))

        car1 = garage.Car(name="car1", year=2000, max_people=1, max_goods=2)
        car2 = garage.Car(name="car2", year=2000, max_people=2, max_goods=1)
        car3 = garage.Car(name="car3", year=2000, max_people=2, max_goods=2)

        rental_service = garage.RentalService([car1, car2, car3])
        self.assertListEqual(rental_service.search(3, 1, 1), [(car1, 0), (car2, 0), (car3, 0)])
        self.assertListEqual(rental_service.search(3, 1, 2), [(car1, 0), (car3, 0)])
        self.assertListEqual(rental_service.search(3, 2, 1), [(car2, 0), (car3, 0)])
        self.assertListEqual(rental_service.search(3, 2, 2), [(car3, 0)])

    def test_ex6(self):
        car1 = garage.Car(name="car1", year=2000, max_people=1, max_goods=2)
        car2 = garage.Car(name="car2", year=2000, max_people=2, max_goods=1)
        car3 = garage.Car(name="car3", year=2000, max_people=2, max_goods=2)

        rental_service1 = garage.RentalService([car1, car2])
        rental_service2 = garage.RentalService([car3])
        self.assertListEqual(rental_service1.search(1, 0, 0), [(car1, 0), (car2, 0)])
        self.assertListEqual(rental_service2.search(1, 0, 0), [(car3, 0)])

        self.assertIs(rental_service1.rent(car1), car1)
        self.assertAlmostEqual(car1.tank_capacity, 42, msg="The Car should have a full tank when rented.")
        with self.assertRaises(ValueError,
                               msg="A ValueError should be raised when renting a Car that is already rented"):
            rental_service1.rent(car1)

        self.assertListEqual(rental_service1.search(1, 0, 0), [(car2, 0)])
        self.assertListEqual(rental_service2.search(1, 0, 0), [(car3, 0)])
        self.assertAlmostEqual(rental_service1.dropoff(car1), 0.0, delta=TestGarage.DELTA)
        self.assertListEqual(rental_service1.search(1, 0, 0), [(car2, 0), (car1, 0)])
        self.assertListEqual(rental_service2.search(1, 0, 0), [(car3, 0)])
        with self.assertRaises(ValueError):
            rental_service1.dropoff(car1)

        rental_service2.rent(car3)
        car3.drive(16.129032258)
        self.assertAlmostEqual(rental_service1.dropoff(car3), 4.0, delta=TestGarage.DELTA)


if __name__ == "__main__":
    pytest.main()
