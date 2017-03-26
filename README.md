# Real-time-notifiaction-system
Real-time-notifiaction-system

COMPONENTS

  mongod - The database process.
  mongos - Sharding controller.
  mongo  - The database shell (uses interactive javascript).

UTILITIES

  mongodump         - MongoDB dump tool - for backups, snapshots, etc..
  mongorestore      - MongoDB restore a dump
  mongoexport       - Export a single collection to test (JSON, CSV)
  mongoimport       - Import from JSON or CSV
  mongofiles        - Utility for putting and getting files from MongoDB GridFS
  mongostat         - Show performance statistics
  
  BUILDING
      
  See docs/building.
  
  
RUNNING

  For command line options invoke:

    $ ./mongod --help

  To run a single server database:

    $ mkdir /data/db
    $ ./mongod
    $
    $ # The mongo javascript shell connects to localhost and test database by default:
    $ ./mongo 
    > help
