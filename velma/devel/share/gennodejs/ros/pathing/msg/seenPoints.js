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

class seenPoints {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.indices = null;
      this.confidences = null;
    }
    else {
      if (initObj.hasOwnProperty('indices')) {
        this.indices = initObj.indices
      }
      else {
        this.indices = [];
      }
      if (initObj.hasOwnProperty('confidences')) {
        this.confidences = initObj.confidences
      }
      else {
        this.confidences = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type seenPoints
    // Serialize message field [indices]
    bufferOffset = _arraySerializer.float64(obj.indices, buffer, bufferOffset, null);
    // Serialize message field [confidences]
    bufferOffset = _arraySerializer.float64(obj.confidences, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type seenPoints
    let len;
    let data = new seenPoints(null);
    // Deserialize message field [indices]
    data.indices = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [confidences]
    data.confidences = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.indices.length;
    length += 8 * object.confidences.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'pathing/seenPoints';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a1650ba81512ff9c6b2cf12c61879bc5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] indices
    float64[] confidences
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new seenPoints(null);
    if (msg.indices !== undefined) {
      resolved.indices = msg.indices;
    }
    else {
      resolved.indices = []
    }

    if (msg.confidences !== undefined) {
      resolved.confidences = msg.confidences;
    }
    else {
      resolved.confidences = []
    }

    return resolved;
    }
};

module.exports = seenPoints;
