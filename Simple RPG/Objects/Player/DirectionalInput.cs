using Assets.Scripts.States;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Scripts.Objects.Player
{
    public class DirectionalInput
    {

        private Vector3 NewDirection;

        private DirectionState _NewPlayerDirection;
        public DirectionState NewPlayerDirection { get { return _NewPlayerDirection; } private set { _NewPlayerDirection = value; } }
        public DirectionalInput() { NewPlayerDirection = DirectionState.UP; }

        public Vector3 InputDirection()
        {

            RefreshDirection();

            if (Input.GetKey(KeyCode.W))
            {

                NewPlayerDirection = DirectionState.UP;
                NewDirection += Vector3.up;
                return NewDirection;

            }
            if (Input.GetKey(KeyCode.S))
            {

                NewPlayerDirection = DirectionState.DOWN;
                NewDirection += Vector3.down;
                return NewDirection;

            }
            if (Input.GetKey(KeyCode.A))
            {

                NewPlayerDirection = DirectionState.LEFT;
                NewDirection += Vector3.left;
                return NewDirection;

            }
            if (Input.GetKey(KeyCode.D))
            {

                NewPlayerDirection = DirectionState.RIGHT;
                NewDirection += Vector3.right;
                return NewDirection;

            }

            return NewDirection;

        }

        private void RefreshDirection()
        {

            NewDirection = Vector3.zero;

        }

    }


}
