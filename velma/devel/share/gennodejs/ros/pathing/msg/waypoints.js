// Auto-generated. Do not edit!

// (in-package pathing.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class waypoints {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.xs = null;
      this.ys = null;
    }
    else {
      if (initObj.hasOwnProperty('xs')) {
        this.xs = initObj.xs
      }
      else {
        this.xs = [];
      }
      if (initObj.hasOwnProperty('ys')) {
        this.ys = initObj.ys
      }
      else {
        this.ys = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type waypoints
    // Serialize message field [xs]
    bufferOffset = _arraySerializer.float64(obj.xs, buffer, bufferOffset, null);
    // Serialize message field [ys]
    bufferOffset = _arraySerializer.float64(obj.ys, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type waypoints
    let len;
    let data = new waypoints(null);
    // Deserialize message field [xs]
    data.xs = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [ys]
    data.ys = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.xs.length;
    length += 8 * object.ys.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'pathing/waypoints';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '86ce9604e58ca9c772c5cdb0f6a5a8ac';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] xs
    float64[] ys
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new waypoints(null);
    if (msg.xs !== undefined) {
      resolved.xs = msg.xs;
    }
    else {
      resolved.xs = []
    }

    if (msg.ys !== undefined) {
      resolved.ys = msg.ys;
    }
    else {
      resolved.ys = []
    }

    return resolved;
    }
};

module.exports = waypoints;
