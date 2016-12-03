#!/usr/bin/python

#This is a smoke test that the module can be loaded and executed.
#It does not test that the module is installed correclty
#(here syntax would be 'from ChimeraTK import steppermotor'
import unittest
import steppermotor

class TestImport(unittest.TestCase):

    def test_import(self):
        dmap_file = './devices.dmap'
        steppermotor.setDmapFilePath(dmap_file)
        self.assertEquals(steppermotor.getDmapFilePath(), dmap_file)


if __name__ == '__main__':
    unittest.main()
    
