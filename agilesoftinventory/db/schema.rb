# encoding: UTF-8
# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended that you check this file into your version control system.

ActiveRecord::Schema.define(version: 20171006124236) do

  # These are extensions that must be enabled in order to support this database
  enable_extension "plpgsql"

  create_table "alotdevices", force: :cascade do |t|
    t.string   "empid",      null: false
    t.string   "empfn",      null: false
    t.string   "empln",      null: false
    t.string   "machineid",  null: false
    t.string   "monitorid",  null: false
    t.string   "mouseid",    null: false
    t.string   "keyboardid", null: false
    t.string   "adaptorid",  null: false
    t.datetime "created_at", null: false
    t.datetime "updated_at", null: false
  end

end
