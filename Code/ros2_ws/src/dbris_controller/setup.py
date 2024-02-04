from setuptools import find_packages, setup

package_name = 'dbris_controller'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='o-gee',
    maintainer_email='bdgee925@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "raspi_node = dbris_controller.raspi_node:main",
            "ard_node = dbris_controller.ard_node:main"
        ],
    },
)
