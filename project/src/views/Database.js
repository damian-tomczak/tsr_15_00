function dbInit() {
    var db = LocalStorage.openDatabaseSync("tsr", "", "tsr database", 1000000)
    try {
        db.transaction(function (tx) {
            tx.executeSql("CREATE TABLE IF NOT EXISTS tasks(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT(256), result REAL, url TEXT(256)); ")
            tx.executeSql("INSERT OR IGNORE INTO tasks(id, name, result, url) VALUES(1, 'Sandbox', 'NULL', 'Sandbox.qml'); ")
            tx.executeSql("INSERT OR IGNORE INTO tasks(id, name, result, url) VALUES(2, 'Adding variables', 4.0, 'Adding.qml'); ")
            tx.executeSql("INSERT OR IGNORE INTO tasks(id, name, result, url) VALUES(3, 'Subtracting varaibles', 3.0, 'Subtracting.qml'); ")
            tx.executeSql("INSERT OR IGNORE INTO tasks(id, name, result, url) VALUES(4, 'Modulo', 1.0, 'Modulo.qml'); ")
            tx.executeSql("CREATE TABLE IF NOT EXISTS students (id INTEGER PRIMARY KEY AUTOINCREMENT, contact TEXT (256), login TEXT (256), password TEXT (256));")
            tx.executeSql("INSERT OR IGNORE INTO students (id, contact, login, password) VALUES (1, 'contact@damian-tomczak.pl', 'damian28102000', 'password123');")
            tx.executeSql("CREATE TABLE IF NOT EXISTS done_tasks (student_id INTEGER REFERENCES students (id), task_id REFERENCES tasks (id));")
        })
    } catch (err) {
        console.log("Error creating table in database: " + err)
    };
}

function dbGetHandle() {
    try {
        var db = LocalStorage.openDatabaseSync("tsr", "",
            "tsr database", 1000000)
    } catch (err) {
        console.log("Error opening database: " + err)
    }
    return db
}

var user = 1

function getAllTasks() {
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results1 = tx.executeSql('SELECT * FROM tasks')
        for (var i = 0; i < results1.rows.length; i++) {
            var results2 = tx.executeSql("SELECT * FROM done_tasks WHERE student_id=? AND task_id=?", [user, results1.rows.item(i).id])
            if (results2.rows.length == 0) {
                listModel.append({
                    id: results1.rows.item(i).id,
                    name: results1.rows.item(i).name,
                    result: results1.rows.item(i).result.toString(),
                    url: results1.rows.item(i).url
                })
            }
        }
    })
}


function getUserName() {
    var result = "default"
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results = tx.executeSql('SELECT * FROM students WHERE id=? LIMIT 1', [user])
        result = results.rows.item(0).login
    })
    return result
}

function getGoal(title) {
    var result = "default"
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results = tx.executeSql('SELECT * FROM tasks WHERE url=? LIMIT 1', [title])
        result = results.rows.item(0).result
    })
    return result
}

function completeTask(file) {
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results = tx.executeSql('SELECT * FROM tasks WHERE url=?', [file])
        var file_id = results.rows.item(0).id
        tx.executeSql('INSERT INTO done_tasks VALUES(?, ?)',
            [user, file_id])
    })
}